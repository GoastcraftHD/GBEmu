#include "Emulator.h"

#include "File.h"
#include "Types.h"

#include <chrono>
#include <vector>

namespace Emulator
{
Emulator::Emulator(const std::filesystem::path& romPath)
{
    const std::vector<char> romData = Common::ReadBinaryFile(romPath.string());
    m_ROMHeader = ROMHeader(romData);
    m_RAM = MakeShared<RAM>(romData);
    m_Renderer = MakeUnique<Renderer::Renderer>(m_RAM);
}

void Emulator::Run()
{
    m_CpuThread = std::jthread(
        [this](std::stop_token stopToken)
        {
            while (!stopToken.stop_requested())
            {
                std::chrono::time_point now = std::chrono::steady_clock::now();
                m_CPU.Step(*m_RAM.get());
                std::this_thread::sleep_until(now + std::chrono::seconds(1));
            }
        });

    m_Renderer->Run();
}
} // namespace Emulator
