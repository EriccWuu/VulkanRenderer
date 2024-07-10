#pragma once

#include "vulkan/vulkan.hpp"

namespace huahualib {

const std::string ROOT_PATH = "E:/Doc/ProjectFiles/CPP/VulkanRenderer/";

class Shader final {
public:
    Shader(const std::string& vertSrc, const std::string& fragSrc);
    ~Shader();

    vk::ShaderModule getVertexModule() const;
    vk::ShaderModule getFragmentModule() const;
    const std::vector<vk::DescriptorSetLayout>& getDescriptorSetLayouts() const;

private:
    vk::ShaderModule vertModule_;
    vk::ShaderModule fragModule_;
    std::vector<vk::DescriptorSetLayout> descriptorSetLayouts_;

    void initShaderModules(const std::string& vertSrc, const std::string& fragSrc);
    void initDescriptorSets();

};

}