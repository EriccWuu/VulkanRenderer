#pragma once

#include "vulkan/vulkan.hpp"

namespace huahualib {

class DescriptorManager final {
public:
    DescriptorManager(uint32_t maxFlight);
    ~DescriptorManager();

    std::vector<vk::DescriptorSet> allocateDescriptorSets(const std::vector<vk::DescriptorSetLayout> &setLayouts);
    void freeDescriptorSets(std::vector<vk::DescriptorSet>& sets);

private:
    struct SetInfo {
        vk::DescriptorPool pool;
        vk::DescriptorSet set;
    };

    uint32_t maxFlight_;
    vk::DescriptorPool descriptorPool_;

    void createDescriporPool();
};

}