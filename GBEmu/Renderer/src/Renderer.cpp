#include "Renderer.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Assert.h"
#include "ImGuiImpl.h"

#include <imgui.h>

namespace Renderer
{
Renderer::Renderer()
{
    GBE_ASSERT_OR_EXECUTE(glfwInit(), "Failed to initialize glfw!", return);

    m_Window = MakeUnique<Window>("GBEmu", 800, 600);

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window->GetRawWindow()));

    GBE_ASSERT_OR_EXECUTE(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to initialize glad!",
                          return);

    glViewport(0, 0, 800, 600);

    ImGuiImpl::Init(static_cast<GLFWwindow*>(m_Window->GetRawWindow()));
}

Renderer::~Renderer()
{
    ImGuiImpl::Destroy();
    m_Window.reset();
    glfwTerminate();
}

void Renderer::Run()
{
    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window->GetRawWindow())))
    {
        glfwPollEvents();
        ImGuiImpl::NewFrame();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Begin("Test");
        ImGui::Text("ASDF");
        ImGui::End();

        ImGuiImpl::Render();

        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window->GetRawWindow()));
    }
}
} // namespace Renderer
