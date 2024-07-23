#pragma once

#include "vulkan/vulkan.hpp"
#include "buffer.h"
#include "texture.h"
#include "shader.h"
#include "vertex.h"

namespace huahualib {

class Renderer final {
public:
    Renderer(int maxFlightCount = 2);
    ~Renderer();

    void bindVertices(const std::vector<Vertex>& vertices);
    void bindIndices(const std::vector<uint32_t>& indices);
    void beginRender();
    void render();
    void endRender();
    void present();
    
private:
    int maxFlightCount_;
    int curframe_;
    unsigned int curImageIndex_;
    std::vector<vk::CommandBuffer> cmdBuffers_;

    std::vector<vk::Fence> fences_;
    std::vector<vk::Semaphore> imageAvaliables_;
    std::vector<vk::Semaphore> imageDrawFinsihs_;

    std::unique_ptr<Buffer> vertexBuffer_;
    std::unique_ptr<Buffer> indexBuffer_;

    std::vector<std::unique_ptr<Buffer>> uniformBuffers_;
    std::vector<std::unique_ptr<Buffer>> uniformBuffersVertex_;

    std::vector<std::vector<vk::DescriptorSet>> sets_;

    Image* depthImage;

    Texture* texture;
    vk::Sampler sampler;

    uint32_t num_index;

    void createSemaphore();
    void createFance();
    void createCommandBuffers();
    void createVertexBuffer(size_t size);
    void bufferVertexData(const std::vector<Vertex>& vertices);
    void createIndexBuffer(size_t size);
    void bufferIndexData(const std::vector<uint32_t>& indices);
    void createUniformBuffer();
    void bufferUniformData();
    void allocateDescriporSets();
    void updateSets();
    void createTexture();
    void createSampler();

    void copyBuffer(vk::Buffer src, vk::Buffer dst, size_t srcOffset, size_t dstOffset, size_t size);
};


}