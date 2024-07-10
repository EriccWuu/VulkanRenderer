#pragma onece

#include <memory.h>
#include <optional>

#include "tool.h"
#include "vulkan/vulkan.hpp"
#include "swapchain.h"
#include "shader.h"
#include "render_process.h"
#include "command_manager.h"
#include "descriptor_manager.h"
#include "texture.h"

namespace huahualib {

class Context final {
public:
    struct QueueFamliyIndices {
        std::optional<uint32_t> graphicsQueue;
        std::optional<uint32_t> presentQueue;

        operator bool () const {
            return graphicsQueue.has_value() && presentQueue.has_value();
        }
    };

    vk::Instance instance;          // Vulkan instance
    vk::PhysicalDevice phyDevice;   // Physical device
    vk::Device device;              // Logical device
    vk::Queue graphicsQueue;        // graphics command queue
    vk::Queue presnetQueue;         // presnet command queue
    vk::SurfaceKHR surface;         // Surface
    std::unique_ptr<Swapchain> swapchainPtr;     // Swapchain
    std::unique_ptr<RenderProcess> renderProcessPtr;
    std::unique_ptr<CommandManager> cmdManagerPtr;
    std::unique_ptr<Shader> shaderPtr;
    std::unique_ptr<DescriptorManager> descriptorManagerPtr;
    std::unique_ptr<TextureManager> textureManagerPtr;

    QueueFamliyIndices queueFamilyIndices;

    ~Context();

    static void init(const std::vector<const char*> &extensions, CreateSurfaceFunc func);
    static void quit();
    static Context& getInstance();

    void initSwapchain(int w, int h);
    void initRenderer();
    void initShaderModule();
    void initRenderProcess();
    void initGraphicsPipeline();
    void initCommandPool();
    void initDescriptorPool(uint32_t maxFlight);
    void initTextureManager();

private:
    static Context* instance_;

    Context(const std::vector<const char*> &extensions, CreateSurfaceFunc func);

    void createInstance(const std::vector<const char*> &extensions);
    void createPhysicalDevice();
    void createSurface(CreateSurfaceFunc func);
    void createDevice(vk::SurfaceKHR surface);
    void getQueues();


    void queryQueueFamilyIndices(vk::SurfaceKHR surface);
};

}