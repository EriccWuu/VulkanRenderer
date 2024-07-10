#include "huahualib.h"
#include "vulkan/vulkan.hpp"

namespace huahualib {

std::unique_ptr<Renderer> rendererPtr;

void init(const std::vector<const char*> &extensions, CreateSurfaceFunc func, int w, int h) {
    uint32_t maxFlight = 2;
    Context::init(extensions, func);
    auto& ctx = Context::getInstance();
    ctx.initSwapchain(w, h);
    ctx.initShaderModule();
    ctx.initRenderProcess();
    ctx.initGraphicsPipeline();
    ctx.swapchainPtr->createFrameBuffers(w, h);
    ctx.initCommandPool();
    ctx.initDescriptorPool(maxFlight);
    ctx.initTextureManager();

    rendererPtr.reset(new Renderer(maxFlight));
}

void quit() {
    auto& ctx = Context::getInstance();
    ctx.device.waitIdle();
    rendererPtr.reset();

    ctx.textureManagerPtr.reset();
    ctx.descriptorManagerPtr.reset();
    ctx.shaderPtr.reset();
    ctx.cmdManagerPtr.reset();
    ctx.renderProcessPtr.reset();
    ctx.swapchainPtr.reset();
    Context::quit();
}

Renderer* getRenderer() {
    return rendererPtr.get();
}

}