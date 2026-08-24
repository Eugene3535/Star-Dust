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
    void initCallbacks() noexcept;

    struct GLFWwindow* m_window;
    Camera m_camera;
	VulkanApi m_api;
};