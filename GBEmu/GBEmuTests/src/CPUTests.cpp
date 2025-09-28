#include "CPU.h"
#include "ROM.h"

#include <gtest/gtest.h>

class CPUTests : public testing::Test
{
protected:
    Emulator::ROM rom;
    Emulator::CPU cpu;

    void SetUp() override
    {

        /* std::vector<char> romData(0x200);

        // Entry Point
        romData[0x100] = 0x0;
        romData[0x101] = 0xC3;
        romData[0x102] = 0x50;
        romData[0x103] = 0x01;

        // Game Title
        romData[0x134] = 'T';
        romData[0x135] = 'E';
        romData[0x136] = 'S';
        romData[0x137] = 'T';

        // Cartridge Type
        romData[0x147] = 0x0;

        // ROM Size
        romData[0x148] = 0x0;

        // RAM Size
        romData[0x148] = 0x0;

        rom = Emulator::ROM(std::move(romData));*/

        cpu.Reset();
    }

    void TearDown() override {}
};

TEST_F(CPUTests, Test_NOP_Instruction)
{
    rom.m_RawData[0x0] = 0xFF;
}
