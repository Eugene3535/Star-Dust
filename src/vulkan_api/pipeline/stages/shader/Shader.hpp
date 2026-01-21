#ifndef SHADER_MODULE_HPP
#define SHADER_MODULE_HPP

#include <filesystem>

#include <vulkan/vulkan.h>


class Shader
{
public:
    Shader(const std::filesystem::path& filePath, VkShaderStageFlagBits stage, VkDevice device) noexcept;
    ~Shader();

    VkPipelineShaderStageCreateInfo getInfo() const noexcept;
    bool isValid() const noexcept;

private:
    VkShaderModule        m_module;
    VkShaderStageFlagBits m_stage;
    VkDevice              m_device;
};


#endif // !SHADER_MODULE_HPP