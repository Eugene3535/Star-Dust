#ifndef RENDER_HPP
#define RENDER_HPP

#include <vulkan/vulkan.h>

struct Render
{
    static bool begin(VkCommandBuffer cmd, const struct MainView* view, uint32_t imageIndex) noexcept;
    static bool end(VkCommandBuffer cmd, const struct MainView* view, uint32_t imageIndex) noexcept;
};

#endif // !RENDER_HPP