#pragma once


class GraphicsApi
{
public:
    GraphicsApi() noexcept = default;
    virtual ~GraphicsApi() = default;

    virtual bool createContext()                                 noexcept = 0;
    virtual bool createView(uint64_t windowHandle)               noexcept = 0;
    virtual void drawFrame()                               const noexcept = 0;
    virtual void resize(int width, int height)                   noexcept = 0;
    virtual void processMouseMovement(float xpos, float ypos)    noexcept = 0;
    virtual void processKeyboard(int direction, float deltaTime) noexcept = 0;
};