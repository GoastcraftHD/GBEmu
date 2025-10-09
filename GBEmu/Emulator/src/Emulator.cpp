#include "Emulator.h"

#include "File.h"
#include "Renderer.h"
#include "Types.h"

#include <vector>

namespace Emulator
{
Emulator::Emulator(const std::filesystem::path& romPath)
{
    std::vector<char> romData = Common::ReadBinaryFile(romPath.string());

    m_ROM = ROM(std::move(romData));

    Renderer::Renderer renderer;
    renderer.Run();
}

void Emulator::Run()
{
    while (!m_ShouldStop)
    {
        // m_CPU.Step(m_ROM, m_RAM);
    }
}
} // namespace Emulator
