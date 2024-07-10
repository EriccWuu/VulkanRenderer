#include "buffer.h"
#include "context.h"

namespace huahualib {

Buffer::Buffer(size_t size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags property): size(size) {
    auto& device = Context::getInstance().device;

    // Create buffer
    vk::BufferCreateInfo bufferInfo;
    bufferInfo
        .setSize(size)
        .setUsage(usage)
        .setSharingMode(vk::SharingMode::eExclusive);
    buffer = device.createBuffer(bufferInfo);

    // Query memory size and type
    auto requirements = device.getBufferMemoryRequirements(buffer);
    requireSize = requirements.size;
    auto memTypeIndex = queryMemoryInfo(requirements.memoryTypeBits, property);

    // Allocate memory
    vk::MemoryAllocateInfo allocInfo;
    allocInfo
        .setMemoryTypeIndex(memTypeIndex)
        .setAllocationSize(requireSize);
    memory = device.allocateMemory(allocInfo);

    // Bind Buffer to memory
    device.bindBufferMemory(buffer, memory, 0);

    // Map memory
    if (property & vk::MemoryPropertyFlagBits::eHostVisible) {
        map = device.mapMemory(memory, 0, size);
    } else {
        map = nullptr;
    }
}

Buffer::~Buffer() {
    auto device = Context::getInstance().device;
    if (map) device.unmapMemory(memory);
    device.freeMemory(memory);
    device.destroyBuffer(buffer);
}

uint32_t Buffer::queryMemoryInfo(size_t memTypeBits, vk::MemoryPropertyFlags memProperty) {
    auto properties = Context::getInstance().phyDevice.getMemoryProperties();
    for (int i = 0; i < properties.memoryTypeCount; ++ i) {
        if ((i << 1) & memTypeBits && properties.memoryTypes[i].propertyFlags & memProperty) {
            return i;
            break;
        }
    }

    return 0;
}

}