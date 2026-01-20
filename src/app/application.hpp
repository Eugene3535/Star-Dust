#ifndef APPLICATION_H
#define APPLICATION_H



#include "vulkan_api/pipeline/descriptors/descriptor_pool.hpp"
#include "vulkan_api/pipeline/graphics_pipeline.hpp"
#include "vulkan_api/command_pool/command_buffer_pool.hpp"
#include "vulkan_api/sync/sync_manager.hpp"
#include "vulkan_api/texture/texture2D.hpp"
#include "vulkan_api/buffers//buffer_holder.hpp"
#include "vulkan_api/render/render.hpp"
#include "app/camera/Camera.hpp"


typedef struct
{
    VulkanContext    context;
    MainView         view;
    GraphicsPipeline pipeline;

    VkDescriptorSet descriptorSets[MAX_FRAMES_IN_FLIGHT];
    DescriptorPool descriptorPool;

    CommandBufferPool commandPool;
    SyncManager sync;

    Texture2D texture;

    BufferHolder bufferHolder;
    Buffer vertices;
    Buffer indices;

    bool framebufferResized;
    int32_t width;
    int32_t height;

    Camera camera;
    mat4s modelViewProjectionMatrix;

    GLFWwindow* window;

} VulkanApp;


bool VulkanApp_create(const char* title, int width, int height, VulkanApp* app);
int  VulkanApp_run(VulkanApp* app);
void VulkanApp_destroy(VulkanApp* app);

#endif // !APPLICATION_H