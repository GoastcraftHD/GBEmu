#include "Renderer.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "Assert.h"
#include "ImGuiImpl.h"

#include <format>
#include <imgui.h>

namespace Renderer
{
Renderer::Renderer(SharedPtr<Emulator::ROM> rom) : m_ROM(rom)
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
    while (true)
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        I32 windowWidth, windowHeight;
        glfwGetFramebufferSize(m_Window->GetRawWindow(), &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glfwSwapBuffers(m_Window->GetRawWindow());

#if defined(GBE_DEBUG)
        RenderDebugWindow();
#endif
    }
}

void Renderer::RenderDebugWindow()
{
    glfwMakeContextCurrent(m_DebugWindow->GetRawWindow());

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

    ImGuiWindowFlags debugWindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DebugDockSpace", nullptr, debugWindowFlags);
    ImGui::PopStyleVar(3);

    ImGui::DockSpace(ImGui::GetID("DebugDockSpace"), ImVec2(0.0f, 0.0f));

    ImGui::Begin("Memory View");

    ImGui::ShowDemoWindow();

    U32 numColumns = 17;

    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_RowBg |
                            ImGuiTableFlags_Borders | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersV |
                            ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner |
                            ImGuiTableFlags_HighlightHoveredColumn | ImGuiTableFlags_ScrollY;

    ImGui::BeginTable("RomViewTable", numColumns, flags);
    ImGui::TableSetupColumn(" ");

    for (U32 i = 0; i < numColumns - 1; i++)
    {
        ImGui::TableSetupColumn(std::format("{:#x}", i).c_str());
    }
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();
    for (U32 row = 0; row < m_ROM->GetRawData().size() / 0x10; row++)
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImGuiCol_TableHeaderBg));
        ImGui::Text(std::format("{:#x}", row * 0x10).c_str());

        for (U32 column = 1; column < numColumns; column++)
        {
            ImGui::TableSetColumnIndex(column);
            U32 columnId = row * 0x10 + (column - 1);
            ImGui::Text(std::format("{:#x}", m_ROM->GetRawData()[columnId]).c_str());
        }
    }
    ImGui::EndTable();

    ImGui::End();
    ImGui::End();

    ImGuiImpl::Render();

    I32 windowWidth, windowHeight;
    glfwGetFramebufferSize(m_DebugWindow->GetRawWindow(), &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSwapBuffers(m_DebugWindow->GetRawWindow());

    glfwMakeContextCurrent(m_Window->GetRawWindow());
}
} // namespace Renderer
