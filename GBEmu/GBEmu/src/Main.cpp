#include "Assert.h"
#include "Emulator.h"

#include <filesystem>
#include <print>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::println("No ROM path provided!");
        return -1;
    }

    const std::filesystem::path romPath(argv[1]);

    if (!std::filesystem::exists(romPath))
    {
        std::println("Provided path doesn't exist!");
        return -1;
    }

    Emulator::Emulator emulator(romPath);
    emulator.Run();
}
