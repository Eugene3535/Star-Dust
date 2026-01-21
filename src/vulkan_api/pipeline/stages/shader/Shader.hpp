#ifndef SHADER_MODULE_HPP
#define SHADER_MODULE_HPP

#include <vulkan/vulkan.h>


class Shader
{
public:
    bool loadFromFile(const char* filePath, VkShaderStageFlagBits stage, VkDevice device) noexcept;
    void destroy(VkDevice device) noexcept;

    VkPipelineShaderStageCreateInfo getInfo() const noexcept;

private:
    VkShaderModule        m_module = VK_NULL_HANDLE;
    VkShaderStageFlagBits m_stage;
};


#endif // !SHADER_MODULE_HPP