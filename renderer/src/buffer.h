#pragma once

#include "vulkan/vulkan.hpp"

namespace huahualib {

class Buffer final {
public:
    vk::Buffer buffer;
    vk::DeviceMemory memory;
    void* map;
    size_t size, requireSize;

    Buffer(size_t size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags property);
    ~Buffer();

private:
    uint32_t queryMemoryInfo(size_t memTypeBits, vk::MemoryPropertyFlags memProperty);

};

}