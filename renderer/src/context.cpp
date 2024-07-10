#include "context.h"

namespace huahualib {

Context* Context::instance_ = nullptr;

Context::Context(const std::vector<const char*> &extensions, CreateSurfaceFunc func) {
    createInstance(extensions);
    createPhysicalDevice();
    createSurface(func);
    createDevice(surface);
    getQueues();
}

Context::~Context() {
    instance.destroySurfaceKHR(surface);
    device.destroy();   // destroy logical device. Command queue will be destroied along with logical device
    instance.destroy();
}

void Context::init(const std::vector<const char*> &extensions, CreateSurfaceFunc func) {
    instance_ = new Context(extensions, func);
}

void Context::quit() {
    delete instance_;
}

Context& Context::getInstance() {
    return *instance_;
}

void Context::createInstance(const std::vector<const char*> &extensions) {
    vk::ApplicationInfo appInfo;
    vk::InstanceCreateInfo instanceInfo;
    std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};

    appInfo.setApiVersion(VK_API_VERSION_1_3);

    instanceInfo
        .setPApplicationInfo(&appInfo)
        .setPEnabledLayerNames(layers)
        .setPEnabledExtensionNames(extensions);
    
    try {
        instance = vk::createInstance(instanceInfo);
    } catch (std::exception &e) {
        throw std::runtime_error("Failed to create vulkan instance!\n");
    }

    std::cout << "Vulkan instance created successed.\n";
}

void Context::createPhysicalDevice() {
    auto devices = instance.enumeratePhysicalDevices();
    phyDevice = devices[0];
    std::cout << "Physical Device Name: " << phyDevice.getProperties().deviceName << '\n';
}

void Context::createSurface(CreateSurfaceFunc func) {
    surface = func(instance);
}

void Context::createDevice(vk::SurfaceKHR surface) {
    std::vector<const char*> extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    vk::DeviceCreateInfo deviceInfo;
    std::vector<vk::DeviceQueueCreateInfo> queueInfos;
    float priority = 1.f;
    queryQueueFamilyIndices(surface);
    if (queueFamilyIndices.graphicsQueue.value() == queueFamilyIndices.presentQueue.value()) {
        vk::DeviceQueueCreateInfo queueInfo;
        queueInfo
            .setPQueuePriorities(&priority)
            .setQueueCount(1)
            .setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());
        queueInfos.push_back(std::move(queueInfo));
    } else {
        vk::DeviceQueueCreateInfo queueInfo;
        queueInfo
            .setPQueuePriorities(&priority)
            .setQueueCount(1)
            .setQueueFamilyIndex(queueFamilyIndices.graphicsQueue.value());
        queueInfos.push_back(std::move(queueInfo));
        queueInfo
            .setPQueuePriorities(&priority)
            .setQueueCount(1)
            .setQueueFamilyIndex(queueFamilyIndices.presentQueue.value());
        queueInfos.push_back(std::move(queueInfo));
    }

    deviceInfo
        .setQueueCreateInfos(queueInfos)
        .setPEnabledExtensionNames(extensions);

    try {
        device = phyDevice.createDevice(deviceInfo);
    } catch (std::exception &e) {
        throw std::runtime_error("Failed to create logical device!\n");
    }
    std::cout << "Logical device created successed.\n";
}

void Context::initSwapchain(int w, int h) {
    swapchainPtr.reset(new Swapchain(surface, w, h));
}

void Context::initCommandPool() {
    cmdManagerPtr = std::make_unique<CommandManager>();
}

void Context::initRenderProcess() {
    renderProcessPtr = std::make_unique<RenderProcess>();
}

void Context::initGraphicsPipeline() {
    renderProcessPtr->createGraphicsPipeline(*shaderPtr);
}

void Context::initDescriptorPool(uint32_t maxFlight) {
    descriptorManagerPtr.reset(new DescriptorManager(maxFlight));
}

void Context::initShaderModule() {
    auto vertexSource = readWholeFile(ROOT_PATH + "renderer/assets/shaders/shader.vert.spv");
    auto fragmentSource = readWholeFile(ROOT_PATH + "renderer/assets/shaders/shader.frag.spv");
    shaderPtr = std::make_unique<Shader>(vertexSource, fragmentSource);
}

void Context::initTextureManager() {
    textureManagerPtr.reset(new TextureManager);
}

void Context::getQueues() {
    graphicsQueue = device.getQueue(queueFamilyIndices.graphicsQueue.value(), 0);
    presnetQueue = device.getQueue(queueFamilyIndices.presentQueue.value(), 0);
}

void Context::queryQueueFamilyIndices(vk::SurfaceKHR surface) {
    auto properties = phyDevice.getQueueFamilyProperties();
    for (uint32_t i = 0; i < properties.size(); ++ i) {
        const auto& properity = properties[i];
        if (properity.queueFlags | vk::QueueFlagBits::eGraphics) {
            queueFamilyIndices.graphicsQueue = i;
        }

        if (phyDevice.getSurfaceSupportKHR(i, surface)) {
            queueFamilyIndices.presentQueue = i;
        }

        if (queueFamilyIndices) {
            break;
        }
    }
}

}