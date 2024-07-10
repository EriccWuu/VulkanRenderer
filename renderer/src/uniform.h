#pragma once

#include "vulkan/vulkan.hpp"
#include "glm/glm.hpp"

namespace huahualib {

struct Uniform final {

    glm::vec3 color;

    static vk::DescriptorSetLayoutBinding getLayoutBinding(uint32_t binding, vk::ShaderStageFlags stage) {
        vk::DescriptorSetLayoutBinding layoutBinding;
        layoutBinding
            .setBinding(binding)
            .setDescriptorCount(1)
            .setDescriptorType(vk::DescriptorType::eUniformBuffer)
            .setStageFlags(stage);
        return layoutBinding;
    }
};

struct MVP final {
    glm::mat4 modle;
    glm::mat4 view;
    glm::mat4 proj;
};

}