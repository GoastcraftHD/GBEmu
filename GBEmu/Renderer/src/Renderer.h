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
};
} // namespace Renderer
