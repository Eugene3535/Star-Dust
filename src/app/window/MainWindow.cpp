#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "OpenGLApi.hpp"
#include "VulkanApi.hpp"

#include "window/MainWindow.hpp"

// TODO remove magic numbers
static float lastX = 400;
static float lastY = 300;


MainWindow::MainWindow() noexcept:
    m_glfwWindow(nullptr)
{

}


MainWindow::~MainWindow()
{
    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
}


bool MainWindow::create(const char* title, int width, int height) noexcept
{
    if (glfwInit() != GLFW_TRUE)
        return false;

    bool vulkanAvailable = true;
    m_graphicsApi = std::make_unique<VulkanApi>(m_camera);

    if (!m_graphicsApi->createContext())
    {
        m_graphicsApi.reset(new OpenGLApi(m_camera));
        vulkanAvailable = false;
    }
    
    if (vulkanAvailable)
    {
        if (!createVulkanWindow(title, width, height))
            return false;
    }
    else
    {
        if (!createOpenGLWindow(title, width, height))
            return false;
    }

    glfwSetWindowUserPointer(m_glfwWindow, static_cast<void*>(m_graphicsApi.get()));
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(m_glfwWindow, width * 0.5, height * 0.5);
    initCallbacks();

    m_graphicsApi->resize(width, height);

    return true;
}


int MainWindow::run() noexcept
{
    float deltaTime = 0.f;
    float lastFrame = 0.f;

    while (!glfwWindowShouldClose(m_glfwWindow))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_glfwWindow, true);

        if (glfwGetKey(m_glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
            m_graphicsApi->processKeyboard(Camera::Direction::FORWARD, deltaTime);

        if (glfwGetKey(m_glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
            m_graphicsApi->processKeyboard(Camera::Direction::BACKWARD, deltaTime);

        if (glfwGetKey(m_glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
            m_graphicsApi->processKeyboard(Camera::Direction::LEFT, deltaTime);

        if (glfwGetKey(m_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
            m_graphicsApi->processKeyboard(Camera::Direction::RIGHT, deltaTime);

        m_graphicsApi->drawFrame();

        glfwPollEvents();
        glfwSwapBuffers(m_glfwWindow);
    }

    return 0;
}


bool MainWindow::createOpenGLWindow(const char* title, int width, int height) noexcept
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    if (m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr))
    {
        glfwMakeContextCurrent(m_glfwWindow);
        glfwSwapInterval(1);

        if (!m_graphicsApi->createContext())
            return false;

        if (!m_graphicsApi->createView(0))
            return false;

        m_graphicsApi->resize(width, height);

        return true;
    }

    return false;
}


bool MainWindow::createVulkanWindow(const char* title, int width, int height) noexcept
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    if (m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr); !m_glfwWindow)
        return false;

    uint64_t windowHandle = 0;

#ifdef _WIN32
    windowHandle = reinterpret_cast<uint64_t>(glfwGetWin32Window(m_glfwWindow));
#endif

#ifdef __linux__
    windowHandle = reinterpret_cast<uint64_t>(glfwGetX11Window(m_glfwWindow));
#endif

    if (!windowHandle)
        return false;

    if (!m_graphicsApi->createView(windowHandle))
        return false;

    return true;
}


void MainWindow::initCallbacks() noexcept
{
    glfwSetFramebufferSizeCallback(m_glfwWindow, [](GLFWwindow* window, int width, int height) -> void
    {
        if (auto api = static_cast<VulkanApi*>(glfwGetWindowUserPointer(window)))
        {
            api->resize(width, height);
        }
    });

    glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double xposIn, double yposIn) -> void
    {
        if (auto api = static_cast<VulkanApi*>(glfwGetWindowUserPointer(window)))
        {
            float xpos = (float)xposIn;
            float ypos = (float)yposIn;

            float xoffset = xpos - lastX;
            float yoffset = ypos - lastY;

            lastX = xpos;
            lastY = ypos;

            api->processMouseMovement(xoffset, yoffset);
        }
    });
}