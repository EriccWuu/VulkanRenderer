#pragma once

#include "vulkan/vulkan.hpp"

namespace huahualib {

class Image final {
public:
    vk::Image image;
    vk::ImageView view;
    vk::DeviceMemory memory;

    Image(vk::ImageCreateInfo imageInfo, vk::ImageViewCreateInfo viewInfo, vk::MemoryPropertyFlags memProperty);
    ~Image();
    void initImage(vk::ImageCreateInfo imageInfo, vk::ImageViewCreateInfo viewInfo, vk::MemoryPropertyFlags memProperty);
    void initImageView();
    void allocateImageMem();

    static void createImage(uint32_t w, uint32_t h, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::Image &image, vk::DeviceMemory &imageMem);
    static vk::ImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags);
    static vk::DeviceMemory allocateMemory(vk::DeviceSize size, uint32_t memTypeIndex);

private:
    void createImage(vk::ImageCreateInfo imageInfo);
    void createImageview(vk::ImageViewCreateInfo viewInfo);
    void allocateMemory(vk::MemoryPropertyFlags memProperty);
    static uint32_t queryImageMemoryIndex(size_t memTypeBits, vk::MemoryPropertyFlags memProperty);

};


}