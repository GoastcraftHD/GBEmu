#pragma once

#include "RAM.h"
#include "Types.h"
#include "Window.h"

namespace Renderer
{
class Renderer
{
public:
    Renderer(SharedPtr<Emulator::RAM> ram);
    ~Renderer();

    void Run();

private:
    void RenderDebugWindow();

private:
    UniquePtr<Window> m_Window;
    UniquePtr<Window> m_DebugWindow;

    SharedPtr<Emulator::RAM> m_RAM;
};
} // namespace Renderer
