#pragma once

#include "RAM.h"
#include "ROM.h"
#include "Test.h"
#include "Types.h"

#include <vector>

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

        INS_DEC_B = 0x05,
        INS_DEC_C = 0x0D,
        INS_DEC_D = 0x15,
        INS_DEC_E = 0x1D,
        INS_DEC_H = 0x25,
        INS_DEC_L = 0x2D,
        INS_DEC_HL = 0x35,
        INS_DEC_A = 0x3D,

        INS_INC_B = 0x04,
        INS_INC_C = 0x0C,
        INS_INC_D = 0x14,
        INS_INC_E = 0x1C,
        INS_INC_H = 0x24,
        INS_INC_L = 0x2C,
        INS_INC_HL = 0x34,
        INS_INC_A = 0x3C,

        INS_LD_B_8 = 0x06,
        INS_LD_C_8 = 0x0E,
        INS_LD_HL_NEG_A = 0x32,
        INS_LD_A_HL_POS = 0x2a,
        INS_LD_BC_16 = 0x01,
        INS_LD_DE_16 = 0x11,
        INS_LD_HL_16 = 0x21,
        INS_LD_SP_16 = 0x31,
        INS_LDH_C_A = 0xE2,

        INS_XOR_A_A = 0xAF,

        INS_CP_A_HL = 0xBE,

        INS_JR_NZ_8 = 0x20,
        INS_JP_8 = 0xC3,

        INS_CALL_16 = 0xCD
    };

public:
    CPU();

    void Reset();

    /*
      Executes 1 instruction
     */
    void Step(RAM& ram);

private:
    U8 FetchByte(const RAM& ram, U16 address);
    U16 FetchWord(const RAM& ram, U16 address);

    void WriteByte(RAM& ram, U16 address, U8 data);
    void WriteWord(RAM& ram, U16 address, U16 data);

    const std::string ConvertToASM(U8 instruction) const;

    void DEC_r_8(U8& reg);
    void INC_r_8(U8& reg);
    void LD_rr_16(const RAM& ram, U16& regg);

private:
    Registers m_Registers;
    U64 m_Cycles = 0;

#if defined(GBE_DEBUG)
    std::vector<U16> m_DebugArguments;
#endif

    CPU_TESTS
};
} // namespace Emulator
