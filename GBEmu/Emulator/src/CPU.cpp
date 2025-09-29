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

void CPU::Step(const ROM& rom)
{
    const U8 instruction = FetchByte(rom, m_Registers.PC);
    m_Registers.PC++;

    switch (instruction)
    {
        case INS_NOP:
            {
                m_Cycles++;
                break;
            }
        case INS_JP_NN:
            {
                m_Registers.PC = FetchWord(rom, m_Registers.PC);
                m_Cycles += 4;
                break;
            }
        case INS_CP_HL:
            {
                U8 data = m_Registers.A - FetchByte(rom, m_Registers.HL);
                m_Registers.ZF = data == 0;
                m_Registers.NF = 1;
                m_Registers.HF = GET_BIT(data, 3);
                m_Registers.CF = GET_BIT(data, 7);

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
        case INS_LD_HL_16:
            {
                m_Registers.HL = FetchWord(rom, m_Registers.PC);
                m_Registers.PC += 2;
                m_Cycles += 3;
                break;
            }
        case INS_LD_C_8:
            {
                m_Registers.C = FetchByte(rom, m_Registers.PC);
                m_Registers.PC++;
                m_Cycles += 2;
                break;
            }
        default:
            {
                std::printf("0x%02X is currently not implemented\n", instruction);
                break;
            }
    }
}

U8 CPU::FetchByte(const ROM& rom, U16 Address)
{
    U8 data = rom[Address];

    std::printf("0x%02X\n", data);
    return data;
}

U16 CPU::FetchWord(const ROM& rom, U16 Address)
{
    U16 data = rom[Address];
    data |= rom[Address + 1] << 8;

    std::printf("0x%04X\n", data);
    return data;
}

} // namespace Emulator
