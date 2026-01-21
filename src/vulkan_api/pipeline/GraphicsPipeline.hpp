#ifndef GRAPHICS_PIPELINE_HPP
#define GRAPHICS_PIPELINE_HPP

#include <vector>
#include <span>

#include "vulkan_api/presentation/MainView.hpp"
#include "vulkan_api/pipeline/stages/shader/Shader.hpp"
#include "vulkan_api/pipeline/stages/shader/VertexInputState.hpp"
#include "vulkan_api/pipeline/stages/uniform/descriptor_set_layout.hpp"


struct GraphicsPipeline
{
    struct State
    {
        void setupShaderStages(std::span<const Shader> shaders, std::span<const VertexInputState::AttributeType> attributes) noexcept;
        void setupInputAssembler(const VkPrimitiveTopology primitive)                                                        noexcept;
        void setupViewport()                                                                                                 noexcept;
        void setupRasterization(VkPolygonMode mode)                                                                          noexcept;
        void setupMultisampling()                                                                                            noexcept;
        void setupColorBlending(VkBool32 enabled)                                                                            noexcept;
        void setupDescriptorSetLayout(const DescriptorSetLayout* uniformDescriptorSet)                                       noexcept;

        std::vector<VkPipelineShaderStageCreateInfo> shaderInfo;
        VertexInputState                             vertexInputState;
        VkPipelineInputAssemblyStateCreateInfo       inputAssembly;
        VkPipelineViewportStateCreateInfo            viewportState;
        VkPipelineRasterizationStateCreateInfo       rasterizer;
        VkPipelineMultisampleStateCreateInfo         multisampling;
        VkPipelineColorBlendAttachmentState          colorBlending;
        DescriptorSetLayout                          layoutInfo;
    };

    bool create(const State& state, const MainView& view);
    void destroy(VkDevice device);

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout      layout;
    VkPipeline            handle;
};

#endif // !GRAPHICS_PIPELINE_HPP