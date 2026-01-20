#ifndef VULKAN_CONTEXT_HPP
#define VULKAN_CONTEXT_HPP

#include <vulkan/vulkan.h>


struct VulkanContext
{
    bool create()  noexcept;
    void destroy() noexcept;

    VkInstance       instance             = VK_NULL_HANDLE;
    VkPhysicalDevice GPU                  = VK_NULL_HANDLE;
    VkDevice         device               = VK_NULL_HANDLE;
    VkQueue          queue                = VK_NULL_HANDLE;
    uint32_t         mainQueueFamilyIndex = 0;
};

#endif // !VULKAN_CONTEXT_H