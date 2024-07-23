#include <iostream>
#include "swapchain.h"
#include "context.h"

namespace huahualib {

Swapchain::Swapchain(vk::SurfaceKHR surface, int w, int h): surface(surface) {
    querySwapchainInfo(w, h);
    createSwapchain();
    createImageAndViews();
    createDepthSource();
}

Swapchain::~Swapchain() {
    auto& device = Context::getInstance().device;

    for (auto& framebuffer : frameBuffers) {
        device.destroyFramebuffer(framebuffer);
    }

    for (auto& imageView : imageViews) {
        device.destroyImageView(imageView);
    }

    device.destroyImageView(depthImageView);
    device.freeMemory(depthImageMem);
    device.destroyImage(depthImage);

    device.destroySwapchainKHR(swapchain);
}

void Swapchain::querySwapchainInfo(int w, int h) {
    auto& phyDevice = Context::getInstance().phyDevice;
    auto& surface = Context::getInstance().surface;

    auto formats = phyDevice.getSurfaceFormatsKHR(surface);
    info.format = formats[0];
    for (const auto& format : formats) {
        if (format.format == vk::Format::eR8G8B8A8Srgb &&
            format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                info.format = format;
                break;;
            }
    }

    auto capabilities = phyDevice.getSurfaceCapabilitiesKHR(surface);
    info.imageCount = std::clamp<uint32_t>(2, capabilities.minImageCount, capabilities.maxImageCount);
    info.imageExtent.width = std::clamp<uint32_t>(w, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    info.imageExtent.height = std::clamp<uint32_t>(h, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    info.transform = capabilities.supportedTransforms;

    auto presents = phyDevice.getSurfacePresentModesKHR(surface);
    info.present = vk::PresentModeKHR::eFifo;
    for (const auto& present : presents) {
        if (present == vk::PresentModeKHR::eMailbox) {
            info.present = present;
            break;
        }
    }
}

void Swapchain::createSwapchain() {
    vk::SwapchainCreateInfoKHR swapchainInfo;
    auto queueFamilyIndices = Context::getInstance().queueFamilyIndices;
    swapchainInfo
        .setClipped(vk::True)
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setSurface(Context::getInstance().surface)
        .setImageFormat(info.format.format)
        .setImageColorSpace(info.format.colorSpace)
        .setImageExtent(info.imageExtent)
        .setMinImageCount(info.imageCount)
        .setPresentMode(info.present);

    if (queueFamilyIndices.presentQueue.value() == queueFamilyIndices.graphicsQueue.value()) {
        swapchainInfo
            .setQueueFamilyIndices(queueFamilyIndices.graphicsQueue.value())
            .setImageSharingMode(vk::SharingMode::eExclusive);
    } else {
        std::array indices = {queueFamilyIndices.graphicsQueue.value(), queueFamilyIndices.presentQueue.value()};
        swapchainInfo
            .setQueueFamilyIndices(indices)
            .setImageSharingMode(vk::SharingMode::eConcurrent);
    }

    try {
        swapchain = Context::getInstance().device.createSwapchainKHR(swapchainInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create swapchain!");
    }
    std::cout << "Swapchain created successed." << std::endl;
}

void Swapchain::createImageAndViews() {
    images = Context::getInstance().device.getSwapchainImagesKHR(swapchain);
    imageViews.resize(images.size());

    for (int i = 0; i < images.size(); ++ i) {
        vk::ImageViewCreateInfo imageViewInfo;
        vk::ComponentMapping mapping;
        vk::ImageSubresourceRange range;
        range
            .setBaseMipLevel(0)
            .setLevelCount(1)
            .setBaseArrayLayer(0)
            .setLayerCount(1)
            .setAspectMask(vk::ImageAspectFlagBits::eColor);
        imageViewInfo
            .setImage(images[i])
            .setComponents(mapping)
            .setViewType(vk::ImageViewType::e2D)
            .setFormat(info.format.format)
            .setSubresourceRange(range);
        try {
            imageViews[i] = Context::getInstance().device.createImageView(imageViewInfo);
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to create image view " + std::to_string(i) + "\n");
        }
        std::cout << "Create image view successed. " + std::to_string(i) << std::endl;
    }
}

void Swapchain::createDepthSource() {
    auto& ctx = Context::getInstance();
    auto& device = Context::getInstance().device;
    // Create depth image
    Image::createImage(
        info.imageExtent.width, 
        info.imageExtent.height, 
        vk::Format::eD32Sfloat, vk::ImageTiling::eOptimal, 
        vk::ImageUsageFlagBits::eDepthStencilAttachment, 
        depthImage, depthImageMem);

    // Create image view
    depthImageView = Image::createImageView(
        depthImage, vk::Format::eD32Sfloat, 
        vk::ImageAspectFlagBits::eDepth);

    ctx.cmdManagerPtr->exceuteCommand(ctx.graphicsQueue, [&](vk::CommandBuffer cmdBuf) -> void {
        vk::ImageMemoryBarrier barrier;
        vk::ImageSubresourceRange range;
        range
            .setAspectMask(vk::ImageAspectFlagBits::eDepth)
            .setBaseArrayLayer(0)
            .setLayerCount(1)
            .setBaseMipLevel(0)
            .setLevelCount(1);
        barrier
            .setImage(depthImage)
            .setSubresourceRange(range)
            .setSrcQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setDstQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setOldLayout(vk::ImageLayout::eUndefined)
            .setNewLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal)
            .setSrcAccessMask(vk::AccessFlagBits::eNone)
            .setDstAccessMask(vk::AccessFlagBits::eDepthStencilAttachmentRead | vk::AccessFlagBits::eDepthStencilAttachmentWrite);
        cmdBuf.pipelineBarrier(
            vk::PipelineStageFlagBits::eTopOfPipe, 
            vk::PipelineStageFlagBits::eEarlyFragmentTests, 
            vk::DependencyFlagBits::eByRegion, 
            {}, {}, barrier);
    });

}

void Swapchain::createFrameBuffers(int w, int h) {
    frameBuffers.resize(images.size());
    for (int i = 0; i < frameBuffers.size(); ++ i) {
        std::vector<vk::ImageView> attachments = {imageViews[i], depthImageView};
        vk::FramebufferCreateInfo frameBufferInfo;
        frameBufferInfo
            .setAttachments(attachments)
            .setWidth((uint32_t)w)
            .setHeight((uint32_t)h)
            .setRenderPass(Context::getInstance().renderProcessPtr->renderPass)    // render pass 指定了纹理附件的用途，创建 framebuffer 时无需指定
            .setLayers(1);
        try {
            frameBuffers[i] = Context::getInstance().device.createFramebuffer(frameBufferInfo);
        } catch (const std::exception &e) {
            throw  std::runtime_error("Failed to create framebuffer!\n");
        }
        std::cout << "Frame buffer created successed." + std::to_string(i) << std::endl;
    }
}

}