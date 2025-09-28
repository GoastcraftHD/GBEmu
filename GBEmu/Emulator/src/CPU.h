#pragma once

#include "ROM.h"
#include "Types.h"

namespace Emulator
{
struct Registers
{
    U8 A;

    U8 Z : 1; // Zero flag
    U8 N : 1; // Subtraction flag
    U8 H : 1; // Half Carry flag
    U8 C : 1; // Carry flag

    union
    {
        U16 BC;
        struct
        {
            U8 B;
            U8 C;
        };
    };

    union
    {
        U16 DE;
        struct
        {
            U8 D;
            U8 E;
        };
    };

    union
    {
        U16 HL;
        struct
        {
            U8 H;
            U8 L;
        };
    };

    U8 IR, IE; // Instruction Register | Interrupt Enable
    U16 SP;
    U16 PC;
};

class CPU
{
public:
    static constexpr U8 INS_NOP = 0x00, INS_JP_NN = 0xC3, INS_CP_HL = 0xBE;

public:
    CPU();

    void Reset();

    /*
      Executes 1 instruction
     */
    void Step(const ROM& rom);

private:
    U8 FetchByte(const ROM& rom, U16 Address);
    U16 FetchWord(const ROM& rom, U16 Address);

private:
    Registers m_Registers;
    U64 m_Cycles = 0;
};
} // namespace Emulator
