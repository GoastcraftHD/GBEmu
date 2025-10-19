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
    ROMHeader m_ROMHeader;
    CPU m_CPU;

    SharedPtr<RAM> m_RAM;
    UniquePtr<Renderer::Renderer> m_Renderer;

    std::jthread m_CpuThread;
    std::jthread m_RenderThread;
};
} // namespace Emulator
