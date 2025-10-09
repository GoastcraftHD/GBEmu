#pragma once

#include "Types.h"

#include <string>

namespace Renderer
{
class Window
{
public:
    Window(std::string name, U32 width, U32 height);
    ~Window();

    void* GetRawWindow() const
    {
        return m_Window;
    }

private:
    void* m_Window;
};
} // namespace Renderer
