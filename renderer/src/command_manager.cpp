#include "command_manager.h"
#include "context.h"

namespace huahualib {

CommandManager::CommandManager() {
    cmdPool_ = createCommandPool();
}

vk::CommandPool CommandManager::createCommandPool() {
    auto& ctx = Context::getInstance();

    vk::CommandPoolCreateInfo poolInfo;
    poolInfo
        .setQueueFamilyIndex(ctx.queueFamilyIndices.graphicsQueue.value())
        .setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);
    
    vk::CommandPool pool;
    try {
        pool = ctx.device.createCommandPool(poolInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to created Command Pool\n");
    }
    std::cout << "Command pool created successed!" << std::endl;

    return pool;
}

CommandManager::~CommandManager() {
    Context::getInstance().device.destroyCommandPool(cmdPool_);
}

vk::CommandBuffer CommandManager::createOneCommandBuffer() {
    return createCommandBuffers(1)[0];
}

std::vector<vk::CommandBuffer> CommandManager::createCommandBuffers(uint32_t count) {
    auto& ctx = Context::getInstance();

    vk::CommandBufferAllocateInfo allocInfo;
    allocInfo
        .setCommandPool(cmdPool_)
        .setCommandBufferCount(count)
        .setLevel(vk::CommandBufferLevel::ePrimary);
    
    std::vector<vk::CommandBuffer> cmdBuffers;
    try {
        cmdBuffers = ctx.device.allocateCommandBuffers(allocInfo);
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to allocated command buffer!\n");
    }

    return cmdBuffers;
}

void CommandManager::resetCommand() {
    Context::getInstance().device.resetCommandPool(cmdPool_);
}

void CommandManager::freeCommand(vk::CommandBuffer buffer) {
    Context::getInstance().device.freeCommandBuffers(cmdPool_, buffer);
}


void CommandManager::exceuteCommand(vk::Queue queue, RecordCmdFunc func) {
    auto cmdBuf = createCommandBuffers(1)[0];
    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
    cmdBuf.begin(beginInfo);
        if (func) func(cmdBuf);
    cmdBuf.end();

    vk::SubmitInfo submitInfo;
    submitInfo.setCommandBuffers(cmdBuf);
    queue.submit(submitInfo);
    queue.waitIdle();
    Context::getInstance().device.waitIdle();
    freeCommand(cmdBuf);
}

}