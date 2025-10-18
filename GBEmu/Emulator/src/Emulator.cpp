#include "Emulator.h"

#include "File.h"
#include "Types.h"

#include <chrono>
#include <vector>

namespace Emulator
{
Emulator::Emulator(const std::filesystem::path& romPath)
    : m_ROM(Common::ReadBinaryFile(romPath.string())), m_Renderer(MakeUnique<Renderer::Renderer>(MakeShared<ROM>(m_ROM)))
{
}

void Emulator::Run()
{
    m_CpuThread = std::jthread(
        [this](std::stop_token stopToken)
        {
            while (!stopToken.stop_requested())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // m_CPU.Step(m_ROM, m_RAM);
            }
        });

    m_Renderer->Run();
}
} // namespace Emulator
