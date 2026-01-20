#ifndef VULKAN_TOOLS_HPP
#define VULKAN_TOOLS_HPP

#include <vulkan/vulkan.h>

#include <vulkan_api/utils/Defines.hpp>

namespace vktools
{
    uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice gpu) noexcept;

    VkCommandBuffer begin_single_time_commands(VkDevice device, VkCommandPool pool) noexcept;
    void end_single_time_commands(VkCommandBuffer cmd, VkDevice device, VkCommandPool pool, VkQueue queue) noexcept;

    VkBuffer create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkDeviceMemory* bufferMemory, VkDevice device, VkPhysicalDevice gpu) noexcept;
    void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDevice device, VkCommandPool pool, VkQueue queue) noexcept;

    bool transition_image_layout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkDevice device, VkCommandPool pool, VkQueue queue) noexcept;
    bool copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkDevice device, VkCommandPool pool, VkQueue queue) noexcept;
    bool create_image_2D(VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage* image, VkDeviceMemory* imageMemory, VkPhysicalDevice gpu, VkDevice device) noexcept;
    bool create_image_view_2D(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView* imageView) noexcept;

    VkFormat find_supported_format(const VkFormat* formats, uint32_t count, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice gpu) noexcept;
    VkFormat find_depth_format(VkPhysicalDevice gpu) noexcept;
    bool has_stencil_component(VkFormat format) noexcept;
}

#endif // !VULKAN_TOOLS_HPP