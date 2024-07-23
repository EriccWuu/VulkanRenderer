#include <iostream>
#include "image.h"
#include "context.h"

namespace huahualib {

Image::Image(vk::ImageCreateInfo imageInfo, vk::ImageViewCreateInfo viewInfo, vk::MemoryPropertyFlags memProperty) {
    createImage(imageInfo);
    allocateMemory(memProperty);
    createImageview(viewInfo);
}

Image::~Image() {
    auto& device = Context::getInstance().device;
    device.destroyImageView(view);
    device.freeMemory(memory);
    device.destroyImage(image);
}

void Image::createImage(vk::ImageCreateInfo imageInfo) {
    try {
        image = Context::getInstance().device.createImage(imageInfo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to create image!\n");
    }
}

void Image::createImageview(vk::ImageViewCreateInfo viewInfo) {
    try {
        view = Context::getInstance().device.createImageView(viewInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create image view!\n");
    }
}

void Image::allocateMemory(vk::MemoryPropertyFlags memProperty) {
    auto &device = Context::getInstance().device;
    auto requirements = device.getImageMemoryRequirements(image);
    vk::MemoryAllocateInfo allocInfo;

    uint32_t index = 0;
    auto properties = Context::getInstance().phyDevice.getMemoryProperties();
    for (int i = 0; i < properties.memoryTypeCount; ++ i) {
        if ((i << 1) & requirements.memoryTypeBits && properties.memoryTypes[i].propertyFlags & memProperty) {
            index = i;
        }
    }

    allocInfo
        .setMemoryTypeIndex(index)
        .setAllocationSize(requirements.size);

    try {
        memory = device.allocateMemory(allocInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to allocate image memory!\n");
    }

    device.bindImageMemory(image, memory, 0);
}

void Image::createImage(uint32_t w, uint32_t h, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::Image &image, vk::DeviceMemory &imageMem) {
    auto& device = Context::getInstance().device;
    vk::ImageCreateInfo imageInfo;
    imageInfo
        .setImageType(vk::ImageType::e2D)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setMipLevels(1)
        .setArrayLayers(1)
        .setSamples(vk::SampleCountFlagBits::e1)
        .setExtent({w, h, 1})
        .setFormat(format)
        .setUsage(usage);

    try {
        image = device.createImage(imageInfo);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to create image!\n");
    }

    auto memReq = device.getImageMemoryRequirements(image);
    imageMem = allocateMemory(memReq.size, queryImageMemoryIndex(memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal));

    device.bindImageMemory(image, imageMem, 0);
}


vk::DeviceMemory Image::allocateMemory(vk::DeviceSize size, uint32_t memTypeIndex) {
    vk::DeviceMemory memory;
    vk::MemoryAllocateInfo allocInfo;
    allocInfo
        .setAllocationSize(size)
        .setMemoryTypeIndex(memTypeIndex);
    try {
        memory = Context::getInstance().device.allocateMemory(allocInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to allocate image memory!\n");
    }
    return memory;
}

vk::ImageView Image::createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags) {
    vk::ComponentMapping mapping;
    vk::ImageSubresourceRange range;
    range
        .setAspectMask(aspectFlags)
        .setBaseMipLevel(0)
        .setLevelCount(1)
        .setBaseArrayLayer(0)
        .setLayerCount(1);
    vk::ImageViewCreateInfo viewInfo;
    viewInfo
        .setViewType(vk::ImageViewType::e2D)
        .setImage(image)
        .setFormat(format)
        .setComponents(mapping)
        .setSubresourceRange(range);

    vk::ImageView imageView;
    try {
        imageView = Context::getInstance().device.createImageView(viewInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create image view!\n");
    }

    return imageView;
}

uint32_t Image::queryImageMemoryIndex(size_t memTypeBits, vk::MemoryPropertyFlags memProperty) {
    auto properties = Context::getInstance().phyDevice.getMemoryProperties();
    for (int i = 0; i < properties.memoryTypeCount; ++ i) {
        if ((i << 1) & memTypeBits && properties.memoryTypes[i].propertyFlags & memProperty) {
            return i;
        }
    }
    return 0;
}

}