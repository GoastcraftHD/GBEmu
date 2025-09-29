#include "ROM.h"

#include "File.h"

namespace Emulator
{
ROM::ROM(std::vector<char>&& romData) : m_RawData(std::move(romData))
{
    std::memcpy(&m_Header.EntryPoint, &m_RawData[0x100], 4);

    UniquePtr<char[]> tempTitle = MakeUnique<char[]>(16);
    strcpy_s(tempTitle.get(), 16, &m_RawData[0x134]);
    m_Header.GameTitle = std::string(tempTitle.get());

    if (m_RawData[0x143] == 0xC0)
    {
        m_Header.CGBOnly = true;
    }

    m_Header.CartridgeType = static_cast<CartridgeType>(m_RawData[0x147]);
    m_Header.ROMSize = 32768 * (1I32 << m_RawData[0x148]);

    switch (m_RawData[0x149])
    {
        case 0x2:
            m_Header.RAMSize = 8192 * 1;
            break;
        case 0x3:
            m_Header.RAMSize = 8192 * 4;
            break;
        case 0x4:
            m_Header.RAMSize = 8192 * 16;
            break;
        case 0x5:
            m_Header.RAMSize = 8192 * 8;
            break;
        default:
            break;
    }
}
} // namespace Emulator
