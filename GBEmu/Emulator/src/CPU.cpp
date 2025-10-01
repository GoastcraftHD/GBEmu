#include "CPU.h"

namespace Emulator
{
CPU::CPU()
{
    Reset();
}

void CPU::Reset()
{
    std::memset(&m_Registers, 0, sizeof(Registers));
    m_Registers.PC = 0x100;
}

void CPU::Step(const ROM& rom, RAM& ram)
{
    const U8 instruction = FetchROMByte(rom, m_Registers.PC);
    m_Registers.PC++;

    switch (instruction)
    {
        case INS_NOP:
            {
                m_Cycles++;
                break;
            }
        case INS_DEC_B:
            {
                m_Registers.B--;
                m_Registers.ZF = m_Registers.B == 0;
                m_Registers.NF = 1;
                m_Registers.HF = GET_BIT(m_Registers.B, 3);
                m_Cycles++;
                break;
            }
        case INS_LD_B_8:
            {
                m_Registers.B = FetchROMByte(rom, m_Registers.PC);
                m_Registers.PC++;
                m_Cycles += 2;
                break;
            }
        case INS_LD_C_8:
            {
                m_Registers.C = FetchROMByte(rom, m_Registers.PC);
                m_Registers.PC++;
                m_Cycles += 2;
                break;
            }
        case INS_LD_HL_16:
            {
                m_Registers.HL = FetchROMWord(rom, m_Registers.PC);
                m_Registers.PC += 2;
                m_Cycles += 3;
                break;
            }
        case INS_LD_HL_NEG_A:
            {
                WriteRAMByte(ram, m_Registers.HL, m_Registers.A);
                m_Registers.HL--;
                m_Cycles += 2;
                break;
            }
        case INS_XOR_A_A:
            {
                m_Registers.A = 0;
                m_Registers.ZF = 1;
                m_Registers.NF = 0;
                m_Registers.HF = 0;
                m_Registers.CF = 0;

                m_Cycles++;
                break;
            }
        case INS_CP_A_HL:
            {
                const U8 data = m_Registers.A - FetchRAMByte(ram, m_Registers.HL);
                m_Registers.ZF = data == 0;
                m_Registers.NF = 1;
                m_Registers.HF = GET_BIT(data, 3);
                m_Registers.CF = GET_BIT(data, 7);

                m_Cycles += 2;
                break;
            }
        case INS_JP_NN:
            {
                m_Registers.PC = FetchROMWord(rom, m_Registers.PC);
                m_Cycles += 4;
                break;
            }
        default:
            {
                std::printf("0x%02X is currently not implemented\n", instruction);
                break;
            }
    }
}

U8 CPU::FetchROMByte(const ROM& rom, U16 address) const
{
    const U8 data = rom[address];

#if defined(GBE_DEBUG)
    std::printf("Read ROM: 0x%02X\n", data);
#endif

    return data;
}

U16 CPU::FetchROMWord(const ROM& rom, U16 address) const
{
    U16 data = rom[address];
    data |= rom[address + 1] << 8;

#if defined(GBE_DEBUG)
    std::printf("Read ROM: 0x%04X from 0x%04X\n", data, address);
#endif

    return data;
}

U8 CPU::FetchRAMByte(const RAM& ram, U16 address) const
{
    const U8 data = ram[address];

#if defined(GBE_DEBUG)
    std::printf("Read ROM: 0x%04X from 0x%04X\n", data, address);
#endif

    return data;
}
U16 CPU::FetchRAMWord(const RAM& ram, U16 address) const
{
    U16 data = ram[address];
    data |= ram[address + 1] << 8;

#if defined(GBE_DEBUG)
    std::printf("Read RAM: 0x%04X from 0x%04X\n", data, address);
#endif

    return data;
}

void CPU::WriteRAMByte(RAM& ram, U16 address, U8 data)
{
    ram[address] = data;

#if defined(GBE_DEBUG)
    std::printf("Wrote RAM: 0x%04X at 0x%04X\n", data, address);
#endif
}

} // namespace Emulator
