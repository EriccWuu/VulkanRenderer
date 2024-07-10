#include "descriptor_manager.h"
#include "context.h"

namespace huahualib {

DescriptorManager::DescriptorManager(uint32_t maxFlight): maxFlight_(maxFlight) {
    createDescriporPool();
}

DescriptorManager::~DescriptorManager() {
    Context::getInstance().device.destroyDescriptorPool(descriptorPool_);
}

std::vector<vk::DescriptorSet> DescriptorManager::allocateBufferSets(const std::vector<vk::DescriptorSetLayout> &setLayouts) {
    vk::DescriptorSetAllocateInfo allocInfo;
    allocInfo
        .setDescriptorPool(descriptorPool_)
        .setSetLayouts(setLayouts);
    return Context::getInstance().device.allocateDescriptorSets(allocInfo);
}

std::vector<vk::DescriptorSet> DescriptorManager::allocateImageSets(const std::vector<vk::DescriptorSetLayout> &setLayouts) {
    vk::DescriptorSetAllocateInfo allocInfo;
    allocInfo
        .setDescriptorPool(descriptorPool_)
        .setSetLayouts(setLayouts);
    return Context::getInstance().device.allocateDescriptorSets(allocInfo);
}

void DescriptorManager::createDescriporPool() {
    vk::DescriptorPoolCreateInfo poolInfo;
    std::vector<vk::DescriptorPoolSize> poolSizes(2);
    poolSizes[0]
        .setType(vk::DescriptorType::eUniformBuffer)
        .setDescriptorCount(maxFlight_);
    poolSizes[1]
        .setType(vk::DescriptorType::eCombinedImageSampler)
        .setDescriptorCount(maxFlight_);
    poolInfo
        .setMaxSets(2 * maxFlight_)
        .setPoolSizes(poolSizes);
    try {
        descriptorPool_ = Context::getInstance().device.createDescriptorPool(poolInfo);
        std::cout << "Descriptor pool created successed." << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create destcriptor pool!\n");
    }
}

}