#pragma once

#include "vulkan/vulkan.hpp"
#include "shader.h"

namespace huahualib {

class RenderProcess final {
public:
    vk::Pipeline pipeline;
    vk::PipelineLayout layout;
    vk::RenderPass renderPass;

    RenderProcess();
    ~RenderProcess();

    void createGraphicsPipeline(const Shader& shader);
    void createRenderPass();

private:
    vk::Pipeline createPipeline(const Shader& shader, vk::PrimitiveTopology primitiveTopology);
    vk::PipelineLayout createLayout();
    vk::RenderPass createRenderPass_();
};

}