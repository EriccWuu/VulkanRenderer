#pragma once

#include <vector>
#include "vulkan/vulkan.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include <glm/gtx/hash.hpp>

namespace huahualib {

struct Vertex final {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec3 color;
    glm::vec2 texcoord;

    bool operator==(const Vertex &other) const {
        return pos == other.pos &&
               normal == other.normal &&
               texcoord == other.texcoord &&
               tangent == other.tangent && 
               bitangent == other.bitangent &&
               color == other.color;
    }

    static std::vector<vk::VertexInputAttributeDescription> getAttribute() {
        std::vector<vk::VertexInputAttributeDescription> attributes(6);
        // pos
        attributes[0]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32B32Sfloat)
            .setLocation(0)
            .setOffset(offsetof(Vertex, pos));
        // normal
        attributes[1]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32B32Sfloat)
            .setLocation(1)
            .setOffset(offsetof(Vertex, normal));
        // tangent
        attributes[2]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32B32Sfloat)
            .setLocation(2)
            .setOffset(offsetof(Vertex, tangent));
        // bitangent
        attributes[3]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32B32Sfloat)
            .setLocation(3)
            .setOffset(offsetof(Vertex, bitangent));
        // color
        attributes[4]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32B32Sfloat)
            .setLocation(4)
            .setOffset(offsetof(Vertex, color));
        // texcoord
        attributes[5]
            .setBinding(0)
            .setFormat(vk::Format::eR32G32Sfloat)
            .setLocation(5)
            .setOffset(offsetof(Vertex, texcoord));
        return attributes;
    }

    static vk::VertexInputBindingDescription getBinding() {
        vk::VertexInputBindingDescription binding;
        binding
            .setBinding(0)
            .setInputRate(vk::VertexInputRate::eVertex)
            .setStride(sizeof(Vertex));
        return binding;
    }
};

}

namespace std {
    template<> struct hash<huahualib::Vertex> {
        size_t operator()(huahualib::Vertex const &vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ 
                (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ 
                (hash<glm::vec2>()(vertex.texcoord) << 1);
        }
    };
}