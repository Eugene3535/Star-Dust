#pragma once

#include <memory>

#include "VulkanApiExport.hpp"
#include "GraphicsApi.hpp"


class VK_API VulkanApi final:
    public GraphicsApi
{
public:
    VulkanApi(Camera& camera) noexcept;
    ~VulkanApi();

    bool createContext()                   noexcept override;
    bool createView(uint64_t windowHandle) noexcept override;
    void drawFrame()                 const noexcept override;
    void resize(int width, int height)     noexcept override;

private:
    std::unique_ptr<class Engine> m_engine;
};
