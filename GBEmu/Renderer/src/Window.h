#pragma once

#include "Types.h"

#include <string>

struct GLFWwindow;

namespace Renderer
{
class Window
{
public:
    Window(std::string name, U32 width, U32 height);
    ~Window();

    GLFWwindow* GetRawWindow() const
    {
        return m_Window;
    }

private:
    GLFWwindow* m_Window;
};
} // namespace Renderer
