#pragma once

#include <memory>

#include "Export.hpp"
#include "GraphicsApi.hpp"


class VK_API VulkanApi final:
    public GraphicsApi
{
public:
    VulkanApi() noexcept;
    ~VulkanApi();

    bool createContext() noexcept;
    bool createView(uint64_t windowHandle) noexcept;
    void drawFrame() const noexcept;

    void processMouseMovement(float xpos, float ypos) noexcept;
    void processKeyboard(int direction, float deltaTime) noexcept;

    void resize(int width, int height) noexcept;

private:
    std::unique_ptr<class Engine> m_engine;
};
