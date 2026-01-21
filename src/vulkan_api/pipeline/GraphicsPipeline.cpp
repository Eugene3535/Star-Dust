#include <cstring>

#include <cglm/struct/mat4.h>

#include "vulkan_api/utils/Tools.hpp"
#include "vulkan_api/presentation/MainView.hpp"
#include "vulkan_api/pipeline/GraphicsPipeline.hpp"


GraphicsPipelineState::~GraphicsPipelineState()
{
    free(vertexInputState.attributeDescriptions.data);
}


void GraphicsPipelineState::setupShaderStages(std::span<const Shader> shaders) noexcept
{
    for(const auto shader : shaders)
        shaderInfo.emplace_back(shader.getInfo());
}


void GraphicsPipelineState::setupVertexInput(const VertexInputStateAttributeType* attributes, uint32_t count) noexcept
{
    VertexInputState_create(&vertexInputState, attributes, count); // TODO сюда перенести инициализацию входного состояния вершин 
}


void GraphicsPipelineState::setupInputAssembler(const VkPrimitiveTopology primitive) noexcept
{
    inputAssembly.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.pNext                  = VK_NULL_HANDLE;
    inputAssembly.flags                  = 0;
    inputAssembly.topology               = primitive;
    inputAssembly.primitiveRestartEnable = VK_FALSE;
}


void GraphicsPipelineState::setupViewport() noexcept
{
    viewportState.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.pNext         = VK_NULL_HANDLE;
    viewportState.flags         = 0;
    viewportState.viewportCount = 1;
    viewportState.pViewports    = VK_NULL_HANDLE;
    viewportState.scissorCount  = 1;
    viewportState.pScissors     = VK_NULL_HANDLE;
}


void GraphicsPipelineState::setupRasterization(VkPolygonMode mode) noexcept
{
    rasterizer.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.pNext                   = VK_NULL_HANDLE;
    rasterizer.flags                   = 0;
    rasterizer.depthClampEnable        = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode             = VK_POLYGON_MODE_FILL;
    rasterizer.cullMode                = VK_CULL_MODE_NONE; // TODO Добавить переключение отсечения граней, например VK_CULL_MODE_FRONT_BIT
    rasterizer.frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable         = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.f;
    rasterizer.depthBiasClamp          = 0.f;
    rasterizer.depthBiasSlopeFactor    = 0.f;
    rasterizer.lineWidth               = 1.f;
}


void GraphicsPipelineState::setupMultisampling() noexcept
{
    multisampling.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.pNext                 = VK_NULL_HANDLE;
    multisampling.flags                 = 0;
    multisampling.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
    multisampling.sampleShadingEnable   = VK_FALSE;
    multisampling.minSampleShading      = 1.f;
    multisampling.pSampleMask           = VK_NULL_HANDLE;
    multisampling.alphaToCoverageEnable = VK_FALSE;
    multisampling.alphaToOneEnable      = VK_FALSE;
}


void GraphicsPipelineState::setupColorBlending(VkBool32 enabled) noexcept
{
    colorBlending.blendEnable         = enabled;
    colorBlending.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlending.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlending.colorBlendOp        = VK_BLEND_OP_ADD;
    colorBlending.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlending.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlending.alphaBlendOp        = VK_BLEND_OP_ADD;
    colorBlending.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
}


void GraphicsPipelineState::setupDescriptorSetLayout(const DescriptorSetLayout* uniformDescriptorSet) noexcept
{
    memcpy(&layoutInfo, uniformDescriptorSet, sizeof(DescriptorSetLayout));
}



bool GraphicsPipeline_create(GraphicsPipeline* pipeline, const GraphicsPipelineState* state, const MainView* view)
{
    VkPhysicalDevice GPU    = view->context->GPU;
    VkDevice         device = view->context->device;
    GraphicsPipeline_destroy(pipeline, device); // for recreate case

    const VkFormat colorFormat = view->format;
    const VkFormat depthFormat = vktools::find_depth_format(GPU);

    const VkPipelineVertexInputStateCreateInfo vertexInput = VertexInputState_getInfo(&state->vertexInputState);

    const VkPipelineRenderingCreateInfoKHR pipelineRenderingInfo =
    {
        .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR,
        .pNext                   = VK_NULL_HANDLE,
        .viewMask                = 0,
        .colorAttachmentCount    = 1,
        .pColorAttachmentFormats = &colorFormat,
        .depthAttachmentFormat   = depthFormat,
        .stencilAttachmentFormat = VK_FORMAT_UNDEFINED
    };

    const VkPipelineColorBlendStateCreateInfo colorBlending =
    {
        .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .pNext           = VK_NULL_HANDLE,
        .flags           = 0,
        .logicOpEnable   = VK_FALSE,
        .logicOp         = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments    = &state->colorBlending
    };

    const VkDynamicState dynamicStates[] = 
    {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    const VkPipelineDynamicStateCreateInfo dynamicState = 
    {
        .sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .pNext             = VK_NULL_HANDLE,
        .flags             = 0,
        .dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState),
        .pDynamicStates    = dynamicStates
    };

    const VkDescriptorSetLayoutCreateInfo layoutInfo = DescriptorSetLayout_getInfo(&state->layoutInfo);

    if (vkCreateDescriptorSetLayout(device, &layoutInfo, VK_NULL_HANDLE, &pipeline->descriptorSetLayout) != VK_SUCCESS)
        return false;

    const VkPushConstantRange pushConstantRange = 
    {
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .offset     = 0,
        .size       = sizeof(mat4s)
    };

    const VkPipelineLayoutCreateInfo pipelineLayoutInfo = 
    {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext                  = VK_NULL_HANDLE,
        .flags                  = 0,
        .setLayoutCount         = 1,
        .pSetLayouts            = &pipeline->descriptorSetLayout,
        .pushConstantRangeCount = 1,
        .pPushConstantRanges    = &pushConstantRange
    };

    if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, VK_NULL_HANDLE, &pipeline->layout) != VK_SUCCESS)
        return false;

    const VkPipelineDepthStencilStateCreateInfo depthStencil = 
    {
        .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .pNext                 = VK_NULL_HANDLE,
        .flags                 = 0,
        .depthTestEnable       = VK_TRUE,
        .depthWriteEnable      = VK_TRUE,
        .depthCompareOp        = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable     = VK_FALSE,
        .front                 = {},
        .back                  = {},
        .minDepthBounds        = 0.f,
        .maxDepthBounds        = 1.f
    };

    const VkGraphicsPipelineCreateInfo pipelineInfo = 
    {
        .sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext               = &pipelineRenderingInfo,
        .flags               = 0,
        .stageCount          = static_cast<uint32_t>(state->shaderInfo.size()),
        .pStages             = state->shaderInfo.data(),
        .pVertexInputState   = &vertexInput,
        .pInputAssemblyState = &state->inputAssembly,
        .pTessellationState  = VK_NULL_HANDLE,
        .pViewportState      = &state->viewportState,
        .pRasterizationState = &state->rasterizer,
        .pMultisampleState   = &state->multisampling,
        .pDepthStencilState  = &depthStencil,
        .pColorBlendState    = &colorBlending,
        .pDynamicState       = &dynamicState,
        .layout              = pipeline->layout,
        .renderPass          = VK_NULL_HANDLE,
        .subpass             = 0,
        .basePipelineHandle  = VK_NULL_HANDLE,
        .basePipelineIndex   = 0
    };

    return (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, VK_NULL_HANDLE, &pipeline->handle) == VK_SUCCESS);
}


void GraphicsPipeline_destroy(GraphicsPipeline* pipeline, VkDevice device)
{
    if(pipeline->handle)
    {
        vkDestroyPipeline(device, pipeline->handle, VK_NULL_HANDLE);
        vkDestroyPipelineLayout(device, pipeline->layout, VK_NULL_HANDLE);
        vkDestroyDescriptorSetLayout(device, pipeline->descriptorSetLayout, VK_NULL_HANDLE);

        pipeline->handle              = VK_NULL_HANDLE;
        pipeline->layout              = VK_NULL_HANDLE;
        pipeline->descriptorSetLayout = VK_NULL_HANDLE;
    }
}