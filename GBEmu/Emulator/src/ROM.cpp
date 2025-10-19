#include "ROM.h"

#include "File.h"

namespace Emulator
{
ROMHeader::ROMHeader(const std::vector<char>& romData)
{
    std::memcpy(&EntryPoint, &romData[0x100], 4);

    UniquePtr<char[]> tempTitle = MakeUnique<char[]>(16);
    strcpy_s(tempTitle.get(), 16, &romData[0x134]);
    GameTitle = std::string(tempTitle.get());

    if (romData[0x143] == 0xC0)
    {
        CGBOnly = true;
    }

    CartridgeType = static_cast<CartridgeTypeEnum>(romData[0x147]);
    ROMSize = 32768 * (1I32 << romData[0x148]);

    switch (romData[0x149])
    {
        case 0x2:
            RAMSize = 8192 * 1;
            break;
        case 0x3:
            RAMSize = 8192 * 4;
            break;
        case 0x4:
            RAMSize = 8192 * 16;
            break;
        case 0x5:
            RAMSize = 8192 * 8;
            break;
        default:
            break;
    }
}
} // namespace Emulator
