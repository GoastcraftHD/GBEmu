#pragma once

#include "RAM.h"
#include "ROM.h"
#include "Types.h"

namespace Emulator
{
struct Registers
{
    U8 A;

    U8 ZF : 1; // Zero flag
    U8 NF : 1; // Subtraction flag
    U8 HF : 1; // Half Carry flag
    U8 CF : 1; // Carry flag

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
    enum : U8
    {
        INS_NOP = 0x00,
        INS_JR_NZ_8 = 0x02,
        INS_DEC_B = 0x05,
        INS_LD_B_8 = 0x06,
        INS_LD_C_8 = 0x0E,
        INS_LD_HL_16 = 0x21,
        INS_LD_HL_NEG_A = 0x32,
        INS_XOR_A_A = 0xAF,
        INS_CP_A_HL = 0xBE,
        INS_JP_NN = 0xC3,
    };

public:
    CPU();

    void Reset();

    /*
      Executes 1 instruction
     */
    void Step(const ROM& rom, RAM& ram);

private:
    U8 FetchROMByte(const ROM& rom, U16 address) const;
    U16 FetchROMWord(const ROM& rom, U16 address) const;

    U8 FetchRAMByte(const RAM& ram, U16 address) const;
    U16 FetchRAMWord(const RAM& ram, U16 address) const;

    void WriteRAMByte(RAM& ram, U16 address, U8 data);

private:
    Registers m_Registers;
    U64 m_Cycles = 0;

    CPU_TESTS
};
} // namespace Emulator
