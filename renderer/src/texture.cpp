#include "texture.h"
#include "context.h"
#include "descriptor_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace huahualib {
/*******************************************************
*                        Texture                       *
*******************************************************/
Texture::Texture(std::string_view filename) {
    int w, h, channel;
    stbi_uc* pexels = stbi_load(filename.data(), &w, &h, &channel, STBI_rgb_alpha);

    if (!pexels) {
        throw std::runtime_error("Failed to load image!\n");
    }

    init(pexels, (uint32_t)w, (uint32_t)h);

    stbi_image_free(pexels);
}

Texture::Texture(void* data, uint32_t w, uint32_t h) {
    init(data, w, h);
}

Texture::~Texture() {
    auto& ctx = Context::getInstance();
    ctx.device.destroyImageView(view);
    ctx.device.freeMemory(memory);
    ctx.device.destroyImage(image);
}

void Texture::init(void* data, uint32_t w, uint32_t h) {
    const uint32_t size = w * h * 4;
    std::unique_ptr<Buffer> buffer(new Buffer(
        size, 
        vk::BufferUsageFlagBits::eTransferSrc, 
        vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible
    ));

    memcpy(buffer->map, data, size);

    createImage(w, h);
    allocMemory();

    auto& ctx = Context::getInstance();
    ctx.device.bindImageMemory(image, memory, 0);

    transitionImageLayoutFromUndefineToDst();
    transformDataToImage(*buffer, w, h);
    transitionImageLayoutFromDstToOptimal();

    createImageView();

    std::vector<vk::DescriptorSetLayout> layouts(2, ctx.shaderPtr->getDescriptorSetLayouts()[0]);
    sets = ctx.descriptorManagerPtr->allocateImageSets(layouts);

    // updateDescriptorSet();
}

void Texture::createImage(uint32_t w, uint32_t h) {
    vk::ImageCreateInfo imageInfo;
    imageInfo
        .setImageType(vk::ImageType::e2D)
        .setArrayLayers(1)
        .setMipLevels(1)
        .setExtent({w, h, 1})
        .setFormat(vk::Format::eR8G8B8A8Srgb)
        .setTiling(vk::ImageTiling::eOptimal)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setUsage(vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled)
        .setSamples(vk::SampleCountFlagBits::e1);
    try {
        image = Context::getInstance().device.createImage(imageInfo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to create image!\n");
    }
}

void Texture::createImageView() {
    vk::ImageViewCreateInfo viewInfo;
    vk::ComponentMapping mapping;
    vk::ImageSubresourceRange range;
    range
        .setAspectMask(vk::ImageAspectFlagBits::eColor)
        .setBaseArrayLayer(0)
        .setBaseMipLevel(0)
        .setLayerCount(1)
        .setLevelCount(1);
    viewInfo
        .setImage(image)
        .setComponents(mapping)
        .setSubresourceRange(range)
        .setViewType(vk::ImageViewType::e2D)
        .setFormat(vk::Format::eR8G8B8A8Srgb);
    try {
        view = Context::getInstance().device.createImageView(viewInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create image view!\n");
    }
}

void Texture::allocMemory() {
    auto &device = Context::getInstance().device;
    auto requirements = device.getImageMemoryRequirements(image);
    vk::MemoryAllocateInfo allocInfo;
    uint32_t index = queryImageMemoryIndex(requirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);
    allocInfo
        .setMemoryTypeIndex(index)
        .setAllocationSize(requirements.size);
    try {
        memory = device.allocateMemory(allocInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to allocate image memory!\n");
    }
}

uint32_t Texture::queryImageMemoryIndex(size_t memTypeBits, vk::MemoryPropertyFlags memProperty) {
    auto properties = Context::getInstance().phyDevice.getMemoryProperties();
    for (int i = 0; i < properties.memoryTypeCount; ++ i) {
        if ((i << 1) & memTypeBits && properties.memoryTypes[i].propertyFlags & memProperty) {
            return i;
            break;
        }
    }

    return 0;
}

void Texture::transitionImageLayoutFromUndefineToDst() {
    auto cmdFunc = [&](vk::CommandBuffer cmdBuf) {
        vk::ImageMemoryBarrier barrier;
        vk::ImageSubresourceRange range;
        range
            .setAspectMask(vk::ImageAspectFlagBits::eColor)
            .setLayerCount(1)
            .setBaseArrayLayer(0)
            .setLevelCount(1)
            .setBaseMipLevel(0);
        barrier
            .setImage(image)
            .setSubresourceRange(range)
            .setOldLayout(vk::ImageLayout::eUndefined)
            .setNewLayout(vk::ImageLayout::eTransferDstOptimal)
            .setDstQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setSrcQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setDstAccessMask(vk::AccessFlagBits::eTransferWrite);
        cmdBuf.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, {}, {}, {}, barrier);
    };

    auto& ctx = Context::getInstance();
    ctx.cmdManagerPtr->exceuteCommand(ctx.graphicsQueue, cmdFunc);
}

void Texture::transitionImageLayoutFromDstToOptimal() {
    auto cmdFunc = [&](vk::CommandBuffer cmdBuf) {
        vk::ImageMemoryBarrier barrier;
        vk::ImageSubresourceRange range;
        range
            .setAspectMask(vk::ImageAspectFlagBits::eColor)
            .setLayerCount(1)
            .setBaseArrayLayer(0)
            .setLevelCount(1)
            .setBaseMipLevel(0);
        barrier
            .setImage(image)
            .setSubresourceRange(range)
            .setOldLayout(vk::ImageLayout::eTransferDstOptimal)
            .setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
            .setDstQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setSrcQueueFamilyIndex(vk::QueueFamilyIgnored)
            .setDstAccessMask(vk::AccessFlagBits::eShaderRead);
        cmdBuf.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, {}, {}, {}, barrier);
    };

    auto& ctx = Context::getInstance();
    ctx.cmdManagerPtr->exceuteCommand(ctx.graphicsQueue, cmdFunc);
}

void Texture::transformDataToImage(Buffer& buffer, uint32_t w, uint32_t h) {
    auto cmdFunc = [&](vk::CommandBuffer cmdBuf) {
        vk::ImageSubresourceLayers subsource;
        vk::BufferImageCopy region;
        subsource
            .setBaseArrayLayer(0)
            .setLayerCount(1)
            .setMipLevel(0)
            .setAspectMask(vk::ImageAspectFlagBits::eColor);
        region
            .setImageSubresource(subsource)
            .setBufferImageHeight(0)
            .setBufferRowLength(0)
            .setBufferOffset(0)
            .setImageOffset(0)
            .setImageExtent({w, h, 1});
        cmdBuf.copyBufferToImage(buffer.buffer, image, vk::ImageLayout::eTransferDstOptimal, region);
    };

    auto& ctx = Context::getInstance();
    ctx.cmdManagerPtr->exceuteCommand(ctx.graphicsQueue, cmdFunc);
}

/*******************************************************
*                     TextureManager                   *
*******************************************************/
std::unique_ptr<TextureManager> TextureManager::instance_ = nullptr;

Texture* TextureManager::load(const std::string& filename) {
    datas_.push_back(std::make_unique<Texture>(filename));
    return datas_.back().get();
}

Texture* TextureManager::create(void* data, uint32_t w, uint32_t h) {
    datas_.push_back(std::make_unique<Texture>(data, w, h));
    return datas_.back().get();
}

Texture* TextureManager::get(int i) const {
    return datas_[i].get();
}

int TextureManager::size() {
    return datas_.size();
}

void TextureManager::destroy(Texture* texture) {
    auto it = std::find_if(datas_.begin(), datas_.end(), [&](const std::unique_ptr<Texture>& t) {
        return t.get() == texture;
    });

    if (it != datas_.end()) {
        Context::getInstance().device.waitIdle();
        datas_.erase(it);
        return ;
    }
}

void TextureManager::clear() {
    datas_.clear();
}

}