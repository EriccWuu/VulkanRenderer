#include "renderer.h"
#include "context.h"
#include "command_manager.h"
#include "vertex.h"
#include "uniform.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace huahualib {

Uniform ubo {
    glm::vec3(1.0, 0.5, 0.7)
};

glm::vec3 color = {1.f, 0.5f, 0.1f};

Renderer::Renderer(int maxFlightCount): maxFlightCount_(maxFlightCount), curframe_(0) {
    createCommandBuffers();
    createSemaphore();
    createFance();
    createUniformBuffer();
    bufferUniformData();
    allocateDescriporSets();
    createTexture();
    createSampler();
    updateSets();
}

Renderer::~Renderer() {
    auto& device = Context::getInstance().device;
    auto& cmdManagerPtr = Context::getInstance().cmdManagerPtr;

    for (auto &cmdBuffer : cmdBuffers_) {
        cmdManagerPtr->freeCommand(cmdBuffer);
    }

    for (int i = 0; i < maxFlightCount_; ++ i) {
        device.destroyFence(fences_[i]);
        device.destroySemaphore(imageAvaliables_[i]);
        device.destroySemaphore(imageDrawFinsihs_[i]);
    }

    vertexBuffer_.reset();
    indexBuffer_.reset();

    for (auto& buffer : uniformBuffers_) {
        buffer.reset();
    }

    device.destroySampler(sampler);

}

void Renderer::beginRender() {
    auto& device = Context::getInstance().device;

    if (device.waitForFences(fences_[curframe_], vk::True, std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
        std::cout << "Wair for fence failed!" << std::endl;
    }
    device.resetFences(fences_[curframe_]);

    auto& renderProcessPtr = Context::getInstance().renderProcessPtr;
    auto& swapchainPtr = Context::getInstance().swapchainPtr;

    auto result = device.acquireNextImageKHR(
        Context::getInstance().swapchainPtr->swapchain, 
        std::numeric_limits<uint64_t>::max(),
        imageAvaliables_[curframe_]);

    if (result.result != vk::Result::eSuccess) {
        std::cout << "Acquire next image failed!" <<std::endl;
    }

    curImageIndex_ = result.value;

    auto& cmdBuffer = cmdBuffers_[curframe_];
    cmdBuffer.reset();

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo
        .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);

    cmdBuffer.begin(beginInfo);
}

void Renderer::endRender() {
    auto& cmdBuffer = cmdBuffers_[curframe_];
    cmdBuffer.end();

    std::vector<vk::PipelineStageFlags> stageFlags = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
    vk::SubmitInfo submitInfo;
    submitInfo
        .setCommandBuffers(cmdBuffer)
        .setWaitSemaphores(imageAvaliables_[curframe_])
        .setSignalSemaphores(imageDrawFinsihs_[curframe_])
        .setWaitDstStageMask(stageFlags);
    Context::getInstance().graphicsQueue.submit(submitInfo, fences_[curframe_]);
}

void Renderer::present() {
    auto& ctx = Context::getInstance();
    vk::PresentInfoKHR presentInfo;
    presentInfo
        .setImageIndices(curImageIndex_)
        .setWaitSemaphores(imageDrawFinsihs_[curframe_])
        .setSwapchains(ctx.swapchainPtr->swapchain);
    
    if (ctx.presnetQueue.presentKHR(presentInfo) != vk::Result::eSuccess) {
        std::cout << "Image present failed!" << std::endl;
    }

    curframe_ = (curframe_ + 1) % maxFlightCount_;
}

void Renderer::render() {
    bufferUniformData();

    auto& renderProcessPtr = Context::getInstance().renderProcessPtr;
    auto& swapchainPtr = Context::getInstance().swapchainPtr;

    auto& cmdBuffer = cmdBuffers_[curframe_];

    vk::RenderPassBeginInfo renderPassBeginInfo;
    vk::Rect2D area({0, 0}, swapchainPtr->info.imageExtent);
    std::vector<vk::ClearValue> clearValues(2);
    clearValues[0].setColor({0.f, 0.f, 0.f, 1.f});
    clearValues[1].setDepthStencil({1.f, 0});
    renderPassBeginInfo
        .setRenderPass(renderProcessPtr->renderPass)
        .setRenderArea(area)
        .setFramebuffer(swapchainPtr->frameBuffers[curImageIndex_])
        .setClearValues(clearValues);

    cmdBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, renderProcessPtr->pipeline);
    vk::DeviceSize offset = 0;
    cmdBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, Context::getInstance().renderProcessPtr->layout, 0, sets_[curframe_], {});
    cmdBuffer.bindVertexBuffers(0, vertexBuffer_->buffer, offset);
    cmdBuffer.bindIndexBuffer(indexBuffer_->buffer, 0, vk::IndexType::eUint32);
    cmdBuffer.pushConstants(renderProcessPtr->layout, vk::ShaderStageFlagBits::eFragment, 0, sizeof(glm::vec3), &color);
    cmdBuffer.beginRenderPass(renderPassBeginInfo, {}); {
        cmdBuffer.drawIndexed(num_index, 1, 0, 0, 0);
    } cmdBuffer.endRenderPass();

}

void Renderer::createCommandBuffers() {
    cmdBuffers_ = Context::getInstance().cmdManagerPtr->createCommandBuffers(maxFlightCount_);
}

void Renderer::createSemaphore() {
    auto &device = Context::getInstance().device;
    imageAvaliables_.resize(maxFlightCount_);
    imageDrawFinsihs_.resize(maxFlightCount_);
    vk::SemaphoreCreateInfo semaInfo;
    for (int i = 0; i < maxFlightCount_; ++ i) {
        imageAvaliables_[i] = device.createSemaphore(semaInfo);
        imageDrawFinsihs_[i] = device.createSemaphore(semaInfo);
    }
}

void Renderer::createFance() {
    fences_.resize(maxFlightCount_);
    vk::FenceCreateInfo fenceInfo;
    for (int i = 0; i < maxFlightCount_; ++ i) {
        fenceInfo.setFlags(vk::FenceCreateFlagBits::eSignaled);
        fences_[i] = Context::getInstance().device.createFence(fenceInfo);
    }
}

void Renderer::bindVertices(const std::vector<Vertex>& vertices) {
    createVertexBuffer(sizeof(vertices[0]) * vertices.size());
    bufferVertexData(vertices);
}

void Renderer::createVertexBuffer(size_t size) {
    vertexBuffer_.reset(new Buffer(size, 
        vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, 
        vk::MemoryPropertyFlagBits::eDeviceLocal));
}

void Renderer::bufferVertexData(const std::vector<Vertex>& vertices) {
    vk::DeviceSize size = sizeof(vertices[0]) * vertices.size();
    auto stagingBufferPtr = std::make_unique<Buffer>(size,
        vk::BufferUsageFlagBits::eTransferSrc,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    memcpy(stagingBufferPtr->map, vertices.data(), size);
    copyBuffer(stagingBufferPtr->buffer, vertexBuffer_->buffer, 0, 0, stagingBufferPtr->size);
    stagingBufferPtr.reset();
}

void Renderer::bindIndices(const std::vector<uint32_t>& indices) {
    num_index = indices.size();
    createIndexBuffer(sizeof(indices[0]) * indices.size());
    bufferIndexData(indices);
}

void Renderer::createIndexBuffer(size_t size) {
    indexBuffer_.reset(new Buffer(size,
        vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst,
        vk::MemoryPropertyFlagBits::eDeviceLocal));
}

void Renderer::bufferIndexData(const std::vector<uint32_t>& indices) {
    vk::DeviceSize size = sizeof(indices[0]) * indices.size();
    auto stagingBufferPtr = std::make_unique<Buffer>(size,
        vk::BufferUsageFlagBits::eTransferSrc,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    memcpy(stagingBufferPtr->map, indices.data(), size);
    copyBuffer(stagingBufferPtr->buffer, indexBuffer_->buffer, 0, 0, stagingBufferPtr->size);
    stagingBufferPtr.reset();
}

void Renderer::createUniformBuffer() {
    uniformBuffers_.resize(maxFlightCount_);
    for (int i = 0; i < maxFlightCount_; ++ i) {
        uniformBuffers_[i].reset(new Buffer(sizeof(MVP), 
            vk::BufferUsageFlagBits::eUniformBuffer,
            vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));
    }
}

void Renderer::bufferUniformData() {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    auto& ctx = Context::getInstance();
    float aspect = float(ctx.swapchainPtr->info.imageExtent.width) / ctx.swapchainPtr->info.imageExtent.height;
    MVP mvp;
    mvp.modle = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -6)) * glm::rotate(glm::mat4(1.f), time * glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
    // mvp.modle = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -3)) * glm::scale(glm::mat4(1.f), glm::vec3(0.1f, 0.1f, 0.1f));
    mvp.view = glm::lookAt(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    mvp.proj = glm::perspective(glm::radians(45.f), aspect, 0.5f, 100.f);
    mvp.proj[1][1] *= -1;
    for (int i = 0; i < uniformBuffers_.size(); ++ i) {
        auto& buffer = uniformBuffers_[i];
        memcpy(buffer->map, &mvp, sizeof(mvp));
    }
}

void Renderer::allocateDescriporSets() {
    auto& ctx = Context::getInstance();
    auto layouts = ctx.shaderManagerPtr->get(0)->getDescriptorSetLayouts();
    sets_.resize(maxFlightCount_);
    for (int i = 0; i < sets_.size(); ++ i) {
        for (auto& layout : layouts) {
            sets_[i].push_back(ctx.descriptorManagerPtr->allocateDescriptorSets({layout})[0]);
        }
    }
}

void Renderer::updateSets() {
    for (int i = 0; i < sets_.size(); ++ i) {
        auto& set = sets_[i];

        std::vector<vk::WriteDescriptorSet> writer(2);

        // Buffer set
        vk::DescriptorBufferInfo bufferInfo;
        bufferInfo
            .setBuffer(uniformBuffers_[i]->buffer)
            .setOffset(0)
            .setRange(uniformBuffers_[i]->size);
        writer[0]
            .setDescriptorType(vk::DescriptorType::eUniformBuffer)
            .setBufferInfo(bufferInfo)
            .setDstSet(set[0])
            .setDstBinding(0)
            .setDescriptorCount(1)
            .setDstArrayElement(0);

        // Texture set
        vk::DescriptorImageInfo imageInfo;
        imageInfo
            .setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal)
            .setImageView(Context::getInstance().textureManagerPtr->get(0)->view)
            .setSampler(sampler);
        writer[1]
            .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
            .setImageInfo(imageInfo)
            .setDstSet(set[1])
            .setDstBinding(0)
            .setDstArrayElement(0)
            .setDescriptorCount(1);

        Context::getInstance().device.updateDescriptorSets(writer, {});
    }
}

void Renderer::createTexture() {
    // texture = Context::getInstance().textureManagerPtr->load(ROOT_PATH + "renderer/assets/images/hutao.png");
    // texture = Context::getInstance().textureManagerPtr->load(ROOT_PATH + "renderer/assets/models/keqing/tex/cloth.png");
    texture = Context::getInstance().textureManagerPtr->load(ROOT_PATH + "renderer/assets/models/Red/Red.png");
}

void Renderer::createSampler() {
    vk::SamplerCreateInfo createInfo;
    createInfo
        .setMagFilter(vk::Filter::eLinear)
        .setMinFilter(vk::Filter::eLinear)
        .setAddressModeU(vk::SamplerAddressMode::eRepeat)
        .setAddressModeV(vk::SamplerAddressMode::eRepeat)
        .setAddressModeW(vk::SamplerAddressMode::eRepeat)
        .setAnisotropyEnable(vk::False)
        .setBorderColor(vk::BorderColor::eIntOpaqueBlack)
        .setUnnormalizedCoordinates(vk::False)
        .setCompareEnable(vk::False)
        .setMipmapMode(vk::SamplerMipmapMode::eLinear);
    try {
        sampler = Context::getInstance().device.createSampler(createInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create sampler!\n");
    }
}

void Renderer::copyBuffer(vk::Buffer src, vk::Buffer dst, size_t srcOffset, size_t dstOffset, size_t size) {
    auto& ctx = Context::getInstance();
    ctx.cmdManagerPtr->exceuteCommand(ctx.graphicsQueue, [&](vk::CommandBuffer cmdBuf){
        vk::BufferCopy region;
        region
            .setSrcOffset(srcOffset)
            .setDstOffset(dstOffset)
            .setSize(size);
        cmdBuf.copyBuffer(src, dst, region);
    });
}

}