#include "SDL.h"
#include "SDL_vulkan.h"
#include "iostream"
#include "vector"

#include "huahualib.h"

int width = 1024;
int height = 720;

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
    
    auto renderer = huahualib::getRenderer();

    while (!shouldClose) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
                shouldClose = true;
        }

        renderer->render();
    }

    huahualib::quit();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}