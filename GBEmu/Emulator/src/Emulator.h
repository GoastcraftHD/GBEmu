#pragma once

#include "CPU.h"
#include "RAM.h"
#include "ROM.h"
#include "Renderer.h"

#include <filesystem>
#include <thread>

namespace Emulator
{
class Emulator
{
public:
    Emulator(const std::filesystem::path& romPath);

    void Run();

private:
    ROM m_ROM;
    RAM m_RAM;
    CPU m_CPU;

    UniquePtr<Renderer::Renderer> m_Renderer;

    std::jthread m_CpuThread;
    std::jthread m_RenderThread;
};
} // namespace Emulator
