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
                U8 T = FetchByte(rom, m_Registers.HL);
                m_Cycles += 2;
                break;
            }
        default:
            {
                std::printf("%i is currently not implemented", instruction);
                break;
            }
    }
}

U8 CPU::FetchByte(const ROM& rom, U16 Address)
{
    return rom[Address];
}

U16 CPU::FetchWord(const ROM& rom, U16 Address)
{
    U16 data = rom[Address];
    data |= rom[Address + 1] & 0xFF;

    return data;
}

} // namespace Emulator
