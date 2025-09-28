#include "Emulator.h"

#include "File.h"
#include "Types.h"

#include <print>
#include <vector>

namespace Emulator
{
Emulator::Emulator(const std::filesystem::path& romPath)
{
    std::vector<char> romData = Common::ReadBinaryFile(romPath.string());

    m_ROM = ROM(std::move(romData));
}

void Emulator::Run()
{
    while (!m_ShouldStop)
    {
        m_CPU.Step(m_ROM);
    }
}
} // namespace Emulator
