#include "huahualib.h"
#include "vulkan/vulkan.hpp"

namespace huahualib {

std::unique_ptr<Renderer> rendererPtr;

void init(const std::vector<const char*> &extensions, CreateSurfaceFunc func, int w, int h) {
    uint32_t maxFlight = 2;
    Context::init(extensions, func);
    auto& ctx = Context::getInstance();
    ctx.initCommandPool();
    ctx.initSwapchain(w, h);
    ctx.initShaderManager();
    ctx.initShaderModule();
    // ctx.initCommandPool();
    ctx.initDescriptorPool(maxFlight);
    ctx.initTextureManager();
    ctx.initRenderProcess();
    ctx.initGraphicsPipeline();
    ctx.swapchainPtr->createFrameBuffers(w, h);

    rendererPtr.reset(new Renderer(maxFlight));
}

void quit() {
    auto& ctx = Context::getInstance();
    ctx.device.waitIdle();
    rendererPtr.reset();

    ctx.renderProcessPtr.reset();
    ctx.swapchainPtr.reset();
    ctx.textureManagerPtr.reset();
    ctx.descriptorManagerPtr.reset();
    ctx.shaderManagerPtr.reset();
    ctx.cmdManagerPtr.reset();
    Context::quit();
}

Renderer* getRenderer() {
    return rendererPtr.get();
}

}