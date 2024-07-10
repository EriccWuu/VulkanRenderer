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
        .setFrontFace(vk::FrontFace::eClockwise)
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

    // 8. Color blending
    vk::PipelineColorBlendStateCreateInfo colorBlendInfo;
    vk::PipelineColorBlendAttachmentState attachments;
    attachments
        .setBlendEnable(vk::False)
        .setColorWriteMask(vk::ColorComponentFlagBits::eA |
            vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eG |
            vk::ColorComponentFlagBits::eR);
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
        .setSetLayouts(Context::getInstance().shaderPtr->getDescriptorSetLayouts())
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
    vk::AttachmentDescription attachmentDescription;
    attachmentDescription
        .setFormat(Context::getInstance().swapchainPtr->info.format.format)
        .setInitialLayout(vk::ImageLayout::eUndefined)
        .setFinalLayout(vk::ImageLayout::ePresentSrcKHR)
        .setLoadOp(vk::AttachmentLoadOp::eClear)
        .setStoreOp(vk::AttachmentStoreOp::eStore)
        .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
        .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
        .setSamples(vk::SampleCountFlagBits::e1);

    renderPassInfo.setAttachments(attachmentDescription);
    
    vk::AttachmentReference attachmentRef;
    attachmentRef
        .setLayout(vk::ImageLayout::eColorAttachmentOptimal)
        .setAttachment(0);  // Reference of attachment 0
    
    vk::SubpassDescription subpassDescription;
    subpassDescription
        .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
        .setColorAttachments(attachmentRef);
    
    renderPassInfo.setSubpasses(subpassDescription);
    
    vk::SubpassDependency dependency;
    dependency
        .setSrcSubpass(vk::SubpassExternal)
        .setDstSubpass(0)   // reference to subpass 0
        .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite)
        .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
        .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
    
    renderPassInfo.setDependencies(dependency);

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