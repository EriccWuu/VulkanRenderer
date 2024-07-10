#pragma once


#include <functional>
#include "vulkan/vulkan.hpp"

namespace huahualib {

class CommandManager final {
public:
    using RecordCmdFunc = std::function<void(vk::CommandBuffer&)>;
    CommandManager();
    ~CommandManager();

    vk::CommandBuffer createOneCommandBuffer();
    std::vector<vk::CommandBuffer> createCommandBuffers(uint32_t count);
    void resetCommand();
    void freeCommand(vk::CommandBuffer buffer);
    void exceuteCommand(vk::Queue queue, RecordCmdFunc func);

private:
    vk::CommandPool cmdPool_;

    vk::CommandPool createCommandPool();
};

}