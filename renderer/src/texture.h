#pragma once

#include <string_view>
#include "vulkan/vulkan.hpp"
#include "buffer.h"
#include "image.h"

namespace huahualib {

class Texture final {
public:
    friend class TextureManager;
    vk::Image image;
    vk::ImageView view;
    vk::DeviceMemory memory;

    Texture(std::string_view filename);
    Texture(void* data, uint32_t w, uint32_t h);
    ~Texture();

private:
    void createImage(uint32_t w, uint32_t h);
    void createImageView();
    void allocMemory();
    uint32_t queryImageMemoryIndex(size_t memTypeBits, vk::MemoryPropertyFlags memProperty);
    void transitionImageLayoutFromUndefineToDst();
    void transitionImageLayoutFromDstToOptimal();
    void transformDataToImage(Buffer& buffer, uint32_t w, uint32_t h);

    void init(void* data, uint32_t w, uint32_t h);

};

class TextureManager final {
public:
    static TextureManager& instance() {
        if (!instance_) {
            instance_.reset(new TextureManager);
        }
        return *instance_;
    }

    Texture* load(const std::string& filename);
    Texture* create(void* data, uint32_t w, uint32_t h);
    Texture* get(int i) const;
    int size();
    void destroy(Texture* texture);
    void clear();

private:
    static std::unique_ptr<TextureManager> instance_;
    std::vector<std::unique_ptr<Texture>> datas_;

};

}