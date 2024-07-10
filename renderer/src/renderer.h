#pragma once

#include "vulkan/vulkan.hpp"
#include "buffer.h"
#include "texture.h"

namespace huahualib {

class Renderer final {
public:
    Renderer(int maxFlightCount = 2);
    ~Renderer();

    void render();
    
private:
    int maxFlightCount_;
    int curframe_;
    std::vector<vk::CommandBuffer> cmdBuffers_;
    std::vector<vk::Fence> fences_;
    std::vector<vk::Semaphore> imageAvaliables_;
    std::vector<vk::Semaphore> imageDrawFinsihs_;

    std::unique_ptr<Buffer> vertexBuffer_;
    std::unique_ptr<Buffer> indexBuffer_;

    std::vector<std::unique_ptr<Buffer>> uniformBuffers_;
    std::vector<std::unique_ptr<Buffer>> uniformBuffersVertex_;

    std::vector<vk::DescriptorSet> sets_;

    Texture* texture;
    vk::Sampler sampler;

    void createSemaphore();
    void createFance();
    void createCommandBuffers();
    void createVertexBuffer();
    void bufferVertexData();
    void createIndexBuffer();
    void bufferIndexData();
    void createUniformBuffer();
    void bufferUniformData();
    void allocateDescriporSets();
    void updateSets();
    void createTexture();
    void createSampler();

    void copyBuffer(vk::Buffer src, vk::Buffer dst, size_t srcOffset, size_t dstOffset, size_t size);
};


}