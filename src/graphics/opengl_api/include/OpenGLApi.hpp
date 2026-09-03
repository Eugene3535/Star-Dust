#pragma once

#include <memory>

#include "OpenGLApiExport.hpp"
#include "GraphicsApi.hpp"


class OGL_API OpenGLApi final:
    public GraphicsApi
{
public:
    OpenGLApi(Camera& camera) noexcept;
    ~OpenGLApi();

    bool createContext() noexcept;
    bool createView(uint64_t windowHandle) noexcept;
    void drawFrame() const noexcept;

    void processMouseMovement(float xpos, float ypos) noexcept;
    void processKeyboard(Camera::Direction direction, float deltaTime) noexcept;

    void resize(int width, int height) noexcept;

private:
    void initializeDebug() noexcept;
    
    uint32_t m_uniformBuffer;
    uint32_t m_shaderProgram;
    uint32_t m_vertexBufferObject;
    uint32_t m_vertexArrayObject;
    uint32_t m_texture;

    int32_t m_width = 0;
    int32_t m_height = 0;
};
