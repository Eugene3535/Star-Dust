#ifndef RENDER_H
#define RENDER_H

#include "vulkan_api/presentation/MainView.hpp"


bool render_begin(VkCommandBuffer cmd, const MainView* view, uint32_t imageIndex);
bool render_end(VkCommandBuffer cmd, const MainView* view, uint32_t imageIndex);

#endif // !RENDER_H