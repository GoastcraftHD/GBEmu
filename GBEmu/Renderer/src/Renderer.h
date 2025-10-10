#pragma once

#include "Types.h"
#include "Window.h"

namespace Renderer
{
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void Run();

private:
    UniquePtr<Window> m_Window;

#if defined(GBE_DEBUG)
    UniquePtr<Window> m_DebugWindow;
    void RenderDebugWindow();
#endif
};
} // namespace Renderer
