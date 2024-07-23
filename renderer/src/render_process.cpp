#include "render_process.h"
#include "context.h"
#include "shader.h"
#include "swapchain.h"
#include "vertex.h"
#include "uniform.h"

namespace huahualib {

RenderProcess::RenderProcess() {
    layout = createLayout();
    renderPass = createRenderPass_();
    pipeline = nullptr;
}

RenderProcess::~RenderProcess() {
    auto& device = Context::getInstance().device;
    device.destroyRenderPass(renderPass);
    device.destroyPipelineLayout(layout);
    device.destroyPipeline(pipeline);
}

void RenderProcess::createGraphicsPipeline(const Shader& shader) {
    pipeline = createPipeline(shader, vk::PrimitiveTopology::eTriangleList);
}

void RenderProcess::createRenderPass() {
    renderPass = createRenderPass_();
}

vk::Pipeline RenderProcess::createPipeline(const Shader& shader, vk::PrimitiveTopology primitiveTopology) {
    auto& ctx = Context::getInstance();

    vk::GraphicsPipelineCreateInfo pipelineInfo;

    // 1. Vertex Input
    vk::PipelineVertexInputStateCreateInfo inputStateInfo;
    auto attrib = Vertex::getAttribute();
    auto binding = Vertex::getBinding();
    inputStateInfo
        .setVertexBindingDescriptions(binding)
        .setVertexAttributeDescriptions(attrib);
    pipelineInfo.setPVertexInputState(&inputStateInfo);

    // 2. Vertex assembly
    vk::PipelineInputAssemblyStateCreateInfo assemblyStateInfo;
    assemblyStateInfo.setTopology(vk::PrimitiveTopology::eTriangleList);
    pipelineInfo.setPInputAssemblyState(&assemblyStateInfo);

    // 3. Shader
    std::vector<vk::PipelineShaderStageCreateInfo> stages(2);
    stages[0]
        .setModule(shader.getVertexModule())
        .setPName("main")
        .setStage(vk::ShaderStageFlagBits::eVertex);
    stages[1]
        .setModule(shader.getFragmentModule())
        .setPName("main")
        .setStage(vk::ShaderStageFlagBits::eFragment);
    pipelineInfo.setStages(stages);

    // 4. Viewport
    vk::PipelineViewportStateCreateInfo viewportStateInfo;
    uint32_t width = ctx.swapchainPtr->info.imageExtent.width;
    uint32_t height = ctx.swapchainPtr->info.imageExtent.height;
    vk::Viewport viewport(0, 0, width, height, 0, 1);
    vk::Rect2D scissor({0, 0}, ctx.swapchainPtr->info.imageExtent);
    viewportStateInfo
        .setViewports(viewport)
        .setScissors(scissor);
    pipelineInfo.setPViewportState(&viewportStateInfo);

    // 5. Rasterization
    vk:vk::PipelineRasterizationStateCreateInfo rastInfo;
    rastInfo
        .setCullMode(vk::CullModeFlagBits::eBack)
        .setRasterizerDiscardEnable(vk::False)
        .setFrontFace(vk::FrontFace::eCounterClockwise)
        .setPolygonMode(vk::PolygonMode::eFill)
        .setLineWidth(1);
    pipelineInfo.setPRasterizationState(&rastInfo);

    // 6. Muli-sample
    vk::PipelineMultisampleStateCreateInfo multiSampleInfo;
    multiSampleInfo
        .setSampleShadingEnable(vk::False)
        .setRasterizationSamples(vk::SampleCountFlagBits::e1);
    pipelineInfo.setPMultisampleState(&multiSampleInfo);

    // 7. test - stencil test, depth test
    vk::PipelineDepthStencilStateCreateInfo depthStencilInfo;
    depthStencilInfo
        .setDepthTestEnable(vk::True)
        .setDepthWriteEnable(vk::True)
        .setDepthCompareOp(vk::CompareOp::eLess)
        .setDepthBoundsTestEnable(vk::False)
        .setMinDepthBounds(0.f)
        .setMaxDepthBounds(1.f)
        .setStencilTestEnable(vk::False)
        .setBack({})
        .setFront({});
    pipelineInfo.setPDepthStencilState(&depthStencilInfo);

    // 8. Color blending
    // newRGB = (srcFactor * srcRGB) <op> (dstFactor * dstRGB)
    vk::PipelineColorBlendStateCreateInfo colorBlendInfo;
    vk::PipelineColorBlendAttachmentState attachments;
    attachments
        .setBlendEnable(vk::True)
        .setColorWriteMask(
            vk::ColorComponentFlagBits::eA |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eR)
        .setSrcColorBlendFactor(vk::BlendFactor::eOne)
        .setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha)
        .setColorBlendOp(vk::BlendOp::eAdd)
        .setSrcAlphaBlendFactor(vk::BlendFactor::eOne)
        .setDstAlphaBlendFactor(vk::BlendFactor::eZero)
        .setAlphaBlendOp(vk::BlendOp::eAdd);
    colorBlendInfo
        .setLogicOpEnable(vk::False)
        .setAttachments(attachments);
    pipelineInfo.setPColorBlendState(&colorBlendInfo);

    // 9. renderpass and layout
    pipelineInfo
        .setLayout(layout)
        .setRenderPass(renderPass);

    auto result = Context::getInstance().device.createGraphicsPipeline(nullptr, pipelineInfo);
    if (result.result != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create pipeline!");
    }

    std::cout << "Pipeline created successed." << std::endl;

    return result.value;
}

vk::PipelineLayout RenderProcess::createLayout() {
    vk::PipelineLayoutCreateInfo layoutInfo;
    vk::PushConstantRange range;
    range
        .setOffset(0)
        .setSize(sizeof(glm::vec3))
        .setStageFlags(vk::ShaderStageFlagBits::eFragment);
    layoutInfo
        .setSetLayouts(Context::getInstance().shaderManagerPtr->get(0)->getDescriptorSetLayouts())
        .setPushConstantRanges(range);
    vk::PipelineLayout layout;
    try {
        layout = Context::getInstance().device.createPipelineLayout(layoutInfo);
        std::cout << "Pipeline layout created successed." << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create pipeline layout!\n");
    }
    return layout;
}

vk::RenderPass RenderProcess::createRenderPass_() {
    vk::RenderPassCreateInfo renderPassInfo;

    vk::AttachmentDescription colorAttachmentDescription;
    colorAttachmentDescription
        .setFormat(Context::getInstance().swapchainPtr->info.format.format)
        .setSamples(vk::SampleCountFlagBits::e1)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setFinalLayout(vk::ImageLayout::ePresentSrcKHR)
        .setLoadOp(vk::AttachmentLoadOp::eClear)
        .setStoreOp(vk::AttachmentStoreOp::eStore)
        .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
        .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
    
    vk::AttachmentDescription depthAttachmentDescription;
    depthAttachmentDescription
        .setFormat(vk::Format::eD32Sfloat)
        .setSamples(vk::SampleCountFlagBits::e1)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setFinalLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal)
        .setLoadOp(vk::AttachmentLoadOp::eClear)
        .setStoreOp(vk::AttachmentStoreOp::eDontCare)
        .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
        .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);

    std::vector<vk::AttachmentDescription> attachmentDescriptions = {colorAttachmentDescription, depthAttachmentDescription};

    vk::AttachmentReference colorAttachmentRef;
    colorAttachmentRef
        .setLayout(vk::ImageLayout::eColorAttachmentOptimal)
        .setAttachment(0);  // Reference of attachment 0
    
    vk::AttachmentReference depthAttachmentRef;
    depthAttachmentRef
        .setLayout(vk::ImageLayout::eDepthStencilAttachmentOptimal)
        .setAttachment(1);
    
    vk::SubpassDescription subpassDescription;
    subpassDescription
        .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
        .setPDepthStencilAttachment(&depthAttachmentRef)
        .setColorAttachments(colorAttachmentRef);
    
    vk::SubpassDependency dependency;
    dependency
        .setSrcSubpass(vk::SubpassExternal)
        .setDstSubpass(0)   // reference to subpass 0
        .setSrcAccessMask(vk::AccessFlagBits::eNone)
        .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite)
        .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests)
        .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests);
    
    renderPassInfo
        .setAttachments(attachmentDescriptions)
        .setSubpasses(subpassDescription)
        .setDependencies(dependency);

    vk::RenderPass renderPass;
    try {
        renderPass = Context::getInstance().device.createRenderPass(renderPassInfo);
        std::cout << "Render pass created successed." << std::endl;
    } catch (const std::exception &e) {
        throw std::runtime_error("Failed to create render pass!");
    }
    return renderPass;
}


}