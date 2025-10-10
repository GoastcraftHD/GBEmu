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

#if defined(GBE_DEBUG)
    m_DebugWindow = MakeUnique<Window>("Debug", 800, 600);
    ImGuiImpl::Init(static_cast<GLFWwindow*>(m_DebugWindow->GetRawWindow()));
#endif
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

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        I32 windowWidth, windowHeight;
        glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_Window->GetRawWindow()), &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window->GetRawWindow()));

#if defined(GBE_DEBUG)
        RenderDebugWindow();
#endif
    }
}
#if defined(GBE_DEBUG)
void Renderer::RenderDebugWindow()
{
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_DebugWindow->GetRawWindow()));

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGuiImpl::NewFrame();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DebugDockSpace", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    ImGui::DockSpace(ImGui::GetID("DebugDockSpace"), ImVec2(0.0f, 0.0f));

    ImGui::Begin("Test");
    ImGui::Text("ASDF");
    ImGui::End();
    ImGui::End();

    ImGuiImpl::Render();

    I32 windowWidth, windowHeight;
    glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_DebugWindow->GetRawWindow()), &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSwapBuffers(static_cast<GLFWwindow*>(m_DebugWindow->GetRawWindow()));

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window->GetRawWindow()));
}
#endif
} // namespace Renderer
