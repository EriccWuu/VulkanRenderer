#pragma once

#include "vulkan/vulkan.hpp"

namespace huahualib {

class DescriptorManager final {
public:
    DescriptorManager(uint32_t maxFlight);
    ~DescriptorManager();

    std::vector<vk::DescriptorSet> allocateBufferSets(const std::vector<vk::DescriptorSetLayout> &setLayouts);
    std::vector<vk::DescriptorSet> allocateImageSets(const std::vector<vk::DescriptorSetLayout> &setLayouts);
    void freeDescriptorSets(std::vector<vk::DescriptorSet>& sets);

private:
    uint32_t maxFlight_;
    vk::DescriptorPool descriptorPool_;

    void createDescriporPool();
};

}