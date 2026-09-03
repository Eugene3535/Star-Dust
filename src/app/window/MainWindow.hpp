#pragma once

#include <memory>

#include "VulkanApi.hpp"


class MainWindow
{
public:
    MainWindow() noexcept;
    ~MainWindow();

    bool create(const char* title, int width, int height) noexcept;
    int run() noexcept;

private:
    bool createOpenGLWindow(const char* title, int width, int height) noexcept;
    bool createVulkanWindow(const char* title, int width, int height) noexcept;
    void initCallbacks() noexcept;

    struct GLFWwindow* m_glfwWindow;
    Camera m_camera;
	std::unique_ptr<class GraphicsApi> m_graphicsApi;
};