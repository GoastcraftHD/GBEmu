#include "Window.h"

#include "Assert.h"

#include <GLFW/glfw3.h>

namespace Renderer
{
Window::Window(std::string name, U32 width, U32 height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    m_Window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    GBE_ASSERT(m_Window, "Failed to create window");
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
}
} // namespace Renderer
