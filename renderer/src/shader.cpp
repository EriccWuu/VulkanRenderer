#include "shader.h"
#include "context.h"
#include "uniform.h"

namespace huahualib {

Shader::Shader(const std::string& vertSrc, const std::string& fragSrc) {
    initShaderModules(vertSrc, fragSrc);
    initDescriptorSets();
}

Shader::~Shader() {
    auto device = Context::getInstance().device;
    device.destroyShaderModule(vertModule_);
    device.destroyShaderModule(fragModule_);
    for (auto& set : descriptorSetLayouts_) {
        device.destroyDescriptorSetLayout(set);
    }
}

vk::ShaderModule Shader::getVertexModule() const {
    return vertModule_;
}

vk::ShaderModule Shader::getFragmentModule() const {
    return fragModule_;
}

const std::vector<vk::DescriptorSetLayout>& Shader::getDescriptorSetLayouts() const {
    return descriptorSetLayouts_;
}

void Shader::initShaderModules(const std::string& vertSrc, const std::string& fragSrc) {
    vk::Device& device = Context::getInstance().device;
    vk::ShaderModuleCreateInfo shaderModelInfo;

    shaderModelInfo.codeSize = vertSrc.size();
    shaderModelInfo.pCode = (uint32_t*)vertSrc.data();
    try {
        vertModule_ = device.createShaderModule(shaderModelInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create vertex shader module!");
    }
    std::cout << "Vertex shader module created successed." << std::endl;

    shaderModelInfo.codeSize = fragSrc.size();
    shaderModelInfo.pCode = (uint32_t*)fragSrc.data();
    try {
        fragModule_ = device.createShaderModule(shaderModelInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create vertex shader module!");
    }
    std::cout << "Framgemt shader module created successed." << std::endl;
}

void Shader::initDescriptorSets() {
    vk::DescriptorSetLayoutCreateInfo setLayoutInfo;
    vk::DescriptorSetLayoutBinding uboBinding;
    uboBinding
            .setBinding(0)
            .setDescriptorCount(1)
            .setDescriptorType(vk::DescriptorType::eUniformBuffer)
            .setStageFlags(vk::ShaderStageFlagBits::eVertex);
    vk::DescriptorSetLayoutBinding samplerBinding;
    samplerBinding
        .setBinding(1)
        .setDescriptorCount(1)
        .setDescriptorType(vk::DescriptorType::eCombinedImageSampler)
        .setStageFlags(vk::ShaderStageFlagBits::eFragment);
    std::vector<vk::DescriptorSetLayoutBinding> bindings = {uboBinding, samplerBinding};
    setLayoutInfo.setBindings(bindings);
    vk::DescriptorSetLayout setLayout;
    try {
        setLayout = Context::getInstance().device.createDescriptorSetLayout(setLayoutInfo);
        std::cout << "Descriptor set layout created successed." << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create descriptor set layout!\n");
    }
    descriptorSetLayouts_.push_back(setLayout);
}

}