#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <vector>

#include <GLFW/glfw3.h>

#include "vulkan_api/context/Context.hpp"


struct MainView
{
    bool create(GLFWwindow* window) noexcept;
    bool recreate(bool useDepth) noexcept;
    void destroy() noexcept;

    const VulkanContext* context = VK_NULL_HANDLE;

    VkSurfaceKHR   surface   = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;

    std::vector<VkImage>     images;
    std::vector<VkImageView> imageViews;

//  Depth buffer TODO wrap to struct
    VkImage        depthImage       = VK_NULL_HANDLE;
    VkDeviceMemory depthImageMemory = VK_NULL_HANDLE;
    VkImageView    depthImageView   = VK_NULL_HANDLE;

    VkFormat   format;
    VkExtent2D extent;
};

#endif // !MAIN_VIEW_HPP