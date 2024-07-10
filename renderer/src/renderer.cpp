#include "renderer.h"
#include "context.h"
#include "command_manager.h"
#include "vertex.h"
#include "uniform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace huahualib {

std::array<Vertex, 4> vertices = {{
    {
        glm::vec3(-0.5, -0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(0.0, 0.0)
    },
    {
        glm::vec3(0.5, -0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(1.0, 0.0)
    },
    {
        glm::vec3(0.5, 0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(1.0, 1.0)
    },
    {
        glm::vec3(-0.5, 0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(0.0, 1.0)
    }
}};

std::array<uint32_t, 6> indices = {
    0, 1, 3,
    1, 2, 3
};

Uniform ubo {
    glm::vec3(1.0, 0.5, 0.7)
};

glm::vec3 color = {1.f, 0.5f, 0.1f};

Renderer::Renderer(int maxFlightCount): maxFlightCount_(maxFlightCount), curframe_(0) {
    createCommandBuffers();
    createSemaphore();
    createFance();
    createVertexBuffer();
    bufferVertexData();
    createIndexBuffer();
    bufferIndexData();
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

void Renderer::render() {
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

    bufferUniformData();

    auto imageIndex = result.value;

    auto& cmdBuffer = cmdBuffers_[curframe_];
    cmdBuffer.reset();

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo
        .setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    vk::RenderPassBeginInfo renderPassBeginInfo;
    vk::Rect2D area({0, 0}, swapchainPtr->info.imageExtent);
    vk::ClearValue clearValue = vk::ClearColorValue(std::array<float, 4>{0.f, 0.f, 0.f, 0.f});
    renderPassBeginInfo
        .setRenderPass(renderProcessPtr->renderPass)
        .setRenderArea(area)
        .setFramebuffer(swapchainPtr->frameBuffers[imageIndex])
        .setClearValues(clearValue);


    cmdBuffer.begin(beginInfo); {
        cmdBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, renderProcessPtr->pipeline);
        vk::DeviceSize offset = 0;
        cmdBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, Context::getInstance().renderProcessPtr->layout, 0, sets_[curframe_], {});
        cmdBuffer.bindVertexBuffers(0, vertexBuffer_->buffer, offset);
        cmdBuffer.bindIndexBuffer(indexBuffer_->buffer, 0, vk::IndexType::eUint32);
        cmdBuffer.pushConstants(renderProcessPtr->layout, vk::ShaderStageFlagBits::eFragment, 0, sizeof(glm::vec3), &color);
        cmdBuffer.beginRenderPass(renderPassBeginInfo, {}); {
            cmdBuffer.drawIndexed(indices.size(), 1, 0, 0, 0);
        } cmdBuffer.endRenderPass();

    } cmdBuffer.end();

    std::vector<vk::PipelineStageFlags> stageFlags = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
    vk::SubmitInfo submitInfo;
    submitInfo
        .setCommandBuffers(cmdBuffer)
        .setWaitSemaphores(imageAvaliables_[curframe_])
        .setSignalSemaphores(imageDrawFinsihs_[curframe_])
        .setWaitDstStageMask(stageFlags);
    Context::getInstance().graphicsQueue.submit(submitInfo, fences_[curframe_]);

    vk::PresentInfoKHR presentInfo;
    presentInfo
        .setImageIndices(imageIndex)
        .setWaitSemaphores(imageDrawFinsihs_[curframe_])
        .setSwapchains(swapchainPtr->swapchain);
    
    if (Context::getInstance().presnetQueue.presentKHR(presentInfo) != vk::Result::eSuccess) {
        std::cout << "Image present failed!" << std::endl;
    }

    curframe_ = (curframe_ + 1) % maxFlightCount_;

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

void Renderer::createVertexBuffer() {
    vertexBuffer_.reset(new Buffer(sizeof(vertices), 
        vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, 
        vk::MemoryPropertyFlagBits::eDeviceLocal));
}

void Renderer::bufferVertexData() {
    auto stagingBufferPtr = std::make_unique<Buffer>(sizeof(vertices),
        vk::BufferUsageFlagBits::eTransferSrc,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    memcpy(stagingBufferPtr->map, vertices.data(), sizeof(vertices));
    copyBuffer(stagingBufferPtr->buffer, vertexBuffer_->buffer, 0, 0, stagingBufferPtr->size);
    stagingBufferPtr.reset();
}

void Renderer::createIndexBuffer() {
    indexBuffer_.reset(new Buffer(sizeof(indices),
        vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst,
        vk::MemoryPropertyFlagBits::eDeviceLocal));
}

void Renderer::bufferIndexData() {
    auto stagingBufferPtr = std::make_unique<Buffer>(sizeof(indices),
        vk::BufferUsageFlagBits::eTransferSrc,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    memcpy(stagingBufferPtr->map, indices.data(), sizeof(indices));
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
    mvp.modle = glm::rotate(glm::mat4(1.f), time * glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
    mvp.view = glm::lookAt(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    mvp.proj = glm::perspective(glm::radians(45.f), aspect, 0.5f, 100.f);
    for (int i = 0; i < uniformBuffers_.size(); ++ i) {
        auto& buffer = uniformBuffers_[i];
        memcpy(buffer->map, &mvp, sizeof(mvp));
    }
}

void Renderer::allocateDescriporSets() {
    std::vector<vk::DescriptorSetLayout> layouts(maxFlightCount_, Context::getInstance().shaderPtr->getDescriptorSetLayouts()[0]);
    sets_ = Context::getInstance().descriptorManagerPtr->allocateBufferSets(layouts);
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
            .setDstSet(set)
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
            .setDstSet(set)
            .setDstBinding(1)
            .setDstArrayElement(0)
            .setDescriptorCount(1);

        Context::getInstance().device.updateDescriptorSets(writer, {});
    }
}

void Renderer::createTexture() {
    texture = Context::getInstance().textureManagerPtr->load(ROOT_PATH + "renderer/assets/images/hutao.png");
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