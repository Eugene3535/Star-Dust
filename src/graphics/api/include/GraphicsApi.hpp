#pragma once

#include "camera/Camera.hpp"

class GFX_API GraphicsApi
{
public:
    GraphicsApi(Camera& camera) noexcept;
    virtual ~GraphicsApi();

    virtual bool createContext()                   noexcept = 0;
    virtual bool createView(uint64_t windowHandle) noexcept = 0;
    virtual void drawFrame()                 const noexcept = 0;
    virtual void resize(int width, int height)     noexcept = 0;

    virtual void processMouseMovement(float xpos, float ypos) noexcept = 0;
    virtual void processKeyboard(Camera::Direction direction, float deltaTime) noexcept = 0;

protected:
    Camera& m_camera;
};