#ifndef GRAPHICS_PIPELINE_HPP
#define GRAPHICS_PIPELINE_HPP

#include <vector>
#include <span>

#include "vulkan_api/presentation/MainView.hpp"
#include "vulkan_api/pipeline/stages/shader/Shader.hpp"
#include "vulkan_api/pipeline/stages/vertex/vertex_input_state.hpp"
#include "vulkan_api/pipeline/stages/uniform/descriptor_set_layout.hpp"


struct GraphicsPipelineState
{
    ~GraphicsPipelineState();

    void setupShaderStages(std::span<const Shader> shaders)                                noexcept;
    void setupVertexInput(const VertexInputStateAttributeType* attributes, uint32_t count) noexcept;
    void setupInputAssembler(const VkPrimitiveTopology primitive)                          noexcept;
    void setupViewport()                                                                   noexcept;
    void setupRasterization(VkPolygonMode mode)                                            noexcept;
    void setupMultisampling()                                                              noexcept;
    void setupColorBlending(VkBool32 enabled)                                              noexcept;
    void setupDescriptorSetLayout(const DescriptorSetLayout* uniformDescriptorSet)         noexcept;

    std::vector<VkPipelineShaderStageCreateInfo> shaderInfo;
    VertexInputState                             vertexInputState;
    VkPipelineInputAssemblyStateCreateInfo       inputAssembly;
    VkPipelineViewportStateCreateInfo            viewportState;
    VkPipelineRasterizationStateCreateInfo       rasterizer;
    VkPipelineMultisampleStateCreateInfo         multisampling;
    VkPipelineColorBlendAttachmentState          colorBlending;
    DescriptorSetLayout                          layoutInfo;
};


struct GraphicsPipeline
{
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout      layout;
    VkPipeline            handle;
};


bool GraphicsPipeline_create(GraphicsPipeline* pipeline, const GraphicsPipelineState* state, const MainView* view);
void GraphicsPipeline_destroy(GraphicsPipeline* pipeline, VkDevice device);

#endif // !GRAPHICS_PIPELINE_HPP