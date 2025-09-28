#pragma once

#include "Types.h"

#include <array>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace Emulator
{
enum CartridgeType : U8
{
    ROM_ONLY = 0x00,
    MBC1 = 0x01,
    MBC1_RAM = 0x02,
    MBC1_RAM_BATTERY = 0x03,
    MBC2 = 0x05,
    MBC2_BATTERY = 0x06,
    ROM_RAM = 0x08,
    ROM_RAM_BATTERY = 0x09,
    MMM01 = 0x0B,
    MMM01_RAM = 0x0C,
    MMM01_RAM_BATTERY = 0x0D,
    MBC3_TIMER_BATTERY = 0x0F,
    MBC3_TIMER_RAM_BATTERY = 0x10,
    MBC3 = 0x11,
    MBC3_RAM = 0x12,
    MBC3_RAM_BATTERY = 0x13,
    MBC5 = 0x19,
    MBC5_RAM = 0x1A,
    MBC5_RAM_BATTERY = 0x1B,
    MBC5_RUMBLE = 0x1C,
    MBC5_RUMBLE_RAM = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY = 0x1E,
    MBC6 = 0x20,
    MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
    POCKET_CAMERA = 0xFC,
    BANDAI_TAMA5 = 0xFD,
    HUC3 = 0xFE,
    HUC1_RAM_BATTERY = 0xFF
};

// Incomplete implementation, includes only what is absolutly necessary
struct ROMHeader
{
    std::array<U8, 4> EntryPoint{};
    std::string GameTitle = "";
    bool CGBOnly = false;
    CartridgeType CartridgeType = CartridgeType::ROM_ONLY;
    U32 ROMSize = 32768; // Minimum of 32KiB
    U32 RAMSize = 0;
};

class ROM
{
public:
    ROM() = default;
    ROM(std::vector<char>&& romData);

    const ROMHeader& GetROMHeader() const
    {
        return m_Header;
    }

    const std::vector<char>& GetRawData() const
    {
        return m_RawData;
    }

    U8 operator[](U16 address) const
    {
        return m_RawData[address];
    }

private:
    ROMHeader m_Header;
    std::vector<char> m_RawData;

#if defined(GBE_TESTS)
    class CPUTests;
    friend class CPUTests;
#endif
};
} // namespace Emulator
