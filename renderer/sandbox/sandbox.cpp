#include "SDL.h"
#include "SDL_vulkan.h"
#include "iostream"
#include "vector"

#include "huahualib.h"

int width = 1024;
int height = 720;

std::vector<huahualib::Vertex> vertices = {{
    {
        glm::vec3(-0.5, -0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(0.0, 0.0)
    },
    {
        glm::vec3(0.5, -0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(1.0, 0.0)
    },
    {
        glm::vec3(0.5, 0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(1.0, 1.0)
    },
    {
        glm::vec3(-0.5, 0.5, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec2(0.0, 1.0)
    }
}};

std::vector<uint32_t> indices = {
    0, 1, 3,
    1, 2, 3
};

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("VulkanRenderer", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
    
    if (!window) {
        SDL_Log("Create window failed.");
        exit(2);
    }

    bool shouldClose = false;
    SDL_Event event;

    uint32_t count;
    SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr);
    std::vector<const char*> extensions(count);
    SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data());

    huahualib::init(extensions, 
        [&](vk::Instance instance) -> VkSurfaceKHR {
            VkSurfaceKHR surface;
            if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
                throw std::runtime_error("Failed to create surface!");
            } else {
                std::cerr << "Surface created successed." << std::endl;
            }
            return surface;
        }, width, height);
    
    // std::string objFilename = huahualib::ROOT_PATH + "renderer/assets/models/keqing/keqing.obj";
    // std::string mtlBasedir = huahualib::ROOT_PATH + "renderer/assets/models/keqing";
    std::string objFilename = huahualib::ROOT_PATH + "renderer/assets/models/Red/Red.obj";
    std::string mtlBasedir = huahualib::ROOT_PATH + "renderer/assets/models/Red";
    huahualib::Model model(objFilename, mtlBasedir);
    
    auto renderer = huahualib::getRenderer();
    renderer->bindVertices(model.vertices());
    renderer->bindIndices(model.indices());

    while (!shouldClose) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
                shouldClose = true;
        }

        renderer->beginRender();
        renderer->render();
        renderer->endRender();
        renderer->present();
    }

    huahualib::quit();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}