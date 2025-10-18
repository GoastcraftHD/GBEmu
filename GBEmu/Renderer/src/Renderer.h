#pragma once

#include "ROM.h"
#include "Types.h"
#include "Window.h"

namespace Renderer
{
class Renderer
{
public:
    Renderer(SharedPtr<Emulator::ROM> rom);
    ~Renderer();

    void Run();

private:
    void RenderDebugWindow();

private:
    UniquePtr<Window> m_Window;
    UniquePtr<Window> m_DebugWindow;

    SharedPtr<Emulator::ROM> m_ROM;
};
} // namespace Renderer
