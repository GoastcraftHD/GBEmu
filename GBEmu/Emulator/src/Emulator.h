#pragma once

#include "CPU.h"
#include "RAM.h"
#include "ROM.h"

#include <filesystem>

namespace Emulator
{
class Emulator
{
public:
    Emulator(const std::filesystem::path& romPath);

    void Run();

private:
    bool m_ShouldStop = false;

    ROM m_ROM;
    RAM m_RAM;
    CPU m_CPU;
};
} // namespace Emulator
