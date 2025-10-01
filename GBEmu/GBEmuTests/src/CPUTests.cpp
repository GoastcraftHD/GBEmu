#include "CPU.h"
#include "RAM.h"
#include "ROM.h"

#include <gtest/gtest.h>

namespace Emulator
{

class CPUTests : public testing::Test
{
protected:
    Emulator::ROM rom;
    Emulator::RAM ram;
    Emulator::CPU cpu;

    void SetUp() override
    {
        std::vector<char> romData(0x200);

        rom = Emulator::ROM(std::move(romData));

        cpu.Reset();
    }

    void TearDown() override {}
};

TEST_F(CPUTests, Test_NOP)
{
    rom.m_RawData[0x100] = cpu.INS_NOP;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 1);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_0_DEC_B)
{
    rom.m_RawData[0x100] = cpu.INS_DEC_B;

    cpu.m_Registers.B = 0x20;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 1);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.B, 0x1F);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 1);
    ASSERT_EQ(cpu.m_Registers.HF, 1);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.C, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_1_DEC_B)
{
    rom.m_RawData[0x100] = cpu.INS_DEC_B;

    cpu.m_Registers.B = 0x01;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 1);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.B, 0x00);
    ASSERT_EQ(cpu.m_Registers.ZF, 1);
    ASSERT_EQ(cpu.m_Registers.NF, 1);
    ASSERT_EQ(cpu.m_Registers.HF, 0);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.C, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_LD_B_8)
{
    rom.m_RawData[0x100] = cpu.INS_LD_B_8;
    rom.m_RawData[0x101] = 0xFF;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 2);
    ASSERT_EQ(cpu.m_Registers.PC, 0x102);
    ASSERT_EQ(cpu.m_Registers.B, 0xFF);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.C, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_LD_C_8)
{
    rom.m_RawData[0x100] = cpu.INS_LD_C_8;
    rom.m_RawData[0x101] = 0xFF;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 2);
    ASSERT_EQ(cpu.m_Registers.PC, 0x102);
    ASSERT_EQ(cpu.m_Registers.C, 0xFF);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.B, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_LD_HL_16)
{
    rom.m_RawData[0x100] = cpu.INS_LD_HL_16;
    rom.m_RawData[0x101] = 0x23;
    rom.m_RawData[0x102] = 0x01;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 3);
    ASSERT_EQ(cpu.m_Registers.PC, 0x103);
    ASSERT_EQ(cpu.m_Registers.HL, 0x123);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_LD_HL_NEG_A)
{
    rom.m_RawData[0x100] = cpu.INS_LD_HL_NEG_A;

    cpu.m_Registers.HL = 0x20;
    cpu.m_Registers.A = 0x18;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 2);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.A, 0x18);
    ASSERT_EQ(cpu.m_Registers.HL, 0x1F);
    ASSERT_EQ(ram[0x20], 0x18);

    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_XOR_A_A)
{
    rom.m_RawData[0x100] = cpu.INS_XOR_A_A;

    cpu.m_Registers.A = 0x18;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 1);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 1);

    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}

TEST_F(CPUTests, Test_0_CP_A_HL)
{
    rom.m_RawData[0x100] = cpu.INS_CP_A_HL;

    ram[0x150] = 0x18;

    cpu.m_Registers.A = 0x18;
    cpu.m_Registers.HL = 0x150;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 2);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.A, 0x18);
    ASSERT_EQ(cpu.m_Registers.HL, 0x150);
    ASSERT_EQ(cpu.m_Registers.ZF, 1);
    ASSERT_EQ(cpu.m_Registers.NF, 1);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
    ASSERT_EQ(ram[0x150], 0x18);

    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
}

TEST_F(CPUTests, Test_1_CP_A_HL)
{
    rom.m_RawData[0x100] = cpu.INS_CP_A_HL;

    ram[0x150] = 0x77;

    cpu.m_Registers.A = 0xFF;
    cpu.m_Registers.HL = 0x150;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 2);
    ASSERT_EQ(cpu.m_Registers.PC, 0x101);
    ASSERT_EQ(cpu.m_Registers.A, 0xFF);
    ASSERT_EQ(cpu.m_Registers.HL, 0x150);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 1);
    ASSERT_EQ(cpu.m_Registers.HF, 1);
    ASSERT_EQ(cpu.m_Registers.CF, 1);
    ASSERT_EQ(ram[0x150], 0x77);

    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
}

TEST_F(CPUTests, Test_JP_NN)
{
    rom.m_RawData[0x100] = cpu.INS_JP_NN;
    rom.m_RawData[0x101] = 0x50;
    rom.m_RawData[0x102] = 0x01;

    cpu.Step(rom, ram);

    ASSERT_EQ(cpu.m_Cycles, 4);
    ASSERT_EQ(cpu.m_Registers.PC, 0x150);

    ASSERT_EQ(cpu.m_Registers.A, 0);
    ASSERT_EQ(cpu.m_Registers.BC, 0);
    ASSERT_EQ(cpu.m_Registers.DE, 0);
    ASSERT_EQ(cpu.m_Registers.HL, 0);
    ASSERT_EQ(cpu.m_Registers.SP, 0);
    ASSERT_EQ(cpu.m_Registers.IR, 0);
    ASSERT_EQ(cpu.m_Registers.IE, 0);
    ASSERT_EQ(cpu.m_Registers.ZF, 0);
    ASSERT_EQ(cpu.m_Registers.NF, 0);
    ASSERT_EQ(cpu.m_Registers.HF, 0);
    ASSERT_EQ(cpu.m_Registers.CF, 0);
}
} // namespace Emulator
