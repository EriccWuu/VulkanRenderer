#pragma once

#include "vulkan/vulkan.hpp"
#include "image.h"

namespace huahualib {

class Swapchain final {
public:
    struct SwapchainInfo {
        uint32_t imageCount;
        vk::Extent2D imageExtent;
        vk::SurfaceFormatKHR format;
        vk::SurfaceTransformFlagsKHR transform;
        vk::PresentModeKHR present;
    };

    vk::SurfaceKHR surface;
    vk::SwapchainKHR swapchain;
    SwapchainInfo info;

    std::vector<vk::Image> images;
    std::vector<vk::ImageView> imageViews;

    vk::Image depthImage;
    vk::ImageView depthImageView;
    vk::DeviceMemory depthImageMem;

    std::vector<vk::Framebuffer> frameBuffers;

    Swapchain(vk::SurfaceKHR surface, int w, int h);
    ~Swapchain();

    void createFrameBuffers(int w, int h);

private:
    void createSwapchain();
    void querySwapchainInfo(int w, int h);
    void createImageAndViews();
    void createDepthSource();
};

}