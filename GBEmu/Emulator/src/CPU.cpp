#include "CPU.h"

#include <format>
#include <iostream>
#include <print>
#include <string>

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
    m_Registers.SP = 0xFFFE;
}

void CPU::Step(RAM& ram)
{
#if defined(GBE_DEBUG)
    m_DebugArguments.clear();
#endif

    const U8 instruction = FetchByte(ram, m_Registers.PC);
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
            DEC_r_8(m_Registers.B);
            break;
        }
        case INS_DEC_C:
        {
            DEC_r_8(m_Registers.C);
            break;
        }
        case INS_DEC_D:
        {
            DEC_r_8(m_Registers.D);
            break;
        }
        case INS_DEC_E:
        {
            DEC_r_8(m_Registers.E);
            break;
        }
        case INS_DEC_H:
        {
            DEC_r_8(m_Registers.H);
            break;
        }
        case INS_DEC_L:
        {
            DEC_r_8(m_Registers.L);
            break;
        }
        case INS_DEC_HL:
        {
            ram[m_Registers.HL]--;
            m_Registers.ZF = ram[m_Registers.HL] == 0;
            m_Registers.NF = 1;
            m_Registers.HF = GET_BIT(ram[m_Registers.HL], 3);
            m_Cycles += 3;
            break;
        }
        case INS_DEC_A:
        {
            DEC_r_8(m_Registers.A);
            break;
        }
        case INS_INC_B:
        {
            INC_r_8(m_Registers.B);
            break;
        }
        case INS_INC_C:
        {
            INC_r_8(m_Registers.C);
            break;
        }
        case INS_INC_D:
        {
            INC_r_8(m_Registers.D);
            break;
        }
        case INS_INC_E:
        {
            INC_r_8(m_Registers.E);
            break;
        }
        case INS_INC_H:
        {
            INC_r_8(m_Registers.H);
            break;
        }
        case INS_INC_L:
        {
            INC_r_8(m_Registers.L);
            break;
        }
        case INS_INC_HL:
        {
            ram[m_Registers.HL]++;
            m_Registers.ZF = ram[m_Registers.HL] == 0;
            m_Registers.NF = 0;
            m_Registers.HF = GET_BIT(ram[m_Registers.HL], 3);
            m_Cycles += 3;
            break;
        }
        case INS_INC_A:
        {
            INC_r_8(m_Registers.A);
            break;
        }
        case INS_LD_B_8:
        {
            m_Registers.B = FetchByte(ram, m_Registers.PC);
            m_Registers.PC++;
            m_Cycles += 2;
            break;
        }
        case INS_LD_C_8:
        {
            m_Registers.C = FetchByte(ram, m_Registers.PC);
            m_Registers.PC++;
            m_Cycles += 2;
            break;
        }
        case INS_JR_NZ_8:
        {
            I8 data = static_cast<I8>(FetchByte(ram, m_Registers.PC));
            m_Registers.PC++;

            if (!m_Registers.ZF)
            {
                m_Registers.PC += data;
                m_Cycles++;
            }

            m_Cycles += 2;
            break;
        }
        case INS_LD_HL_NEG_A:
        {
            WriteByte(ram, m_Registers.HL, m_Registers.A);
            m_Registers.HL--;
            m_Cycles += 2;
            break;
        }
        case INS_LD_A_HL_POS:
        {
            m_Registers.A = FetchByte(ram, m_Registers.HL);
            m_Registers.HL++;
            m_Cycles += 2;
            break;
        }
        case INS_LD_BC_16:
        {
            LD_rr_16(ram, m_Registers.BC);
            break;
        }
        case INS_LD_DE_16:
        {
            LD_rr_16(ram, m_Registers.DE);
            break;
        }
        case INS_LD_HL_16:
        {
            LD_rr_16(ram, m_Registers.HL);
            break;
        }
        case INS_LD_SP_16:
        {
            LD_rr_16(ram, m_Registers.SP);
            break;
        }
        case INS_LDH_C_A:
        {
            WriteByte(ram, 0xFF00 + m_Registers.C, m_Registers.A);
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
            const U8 data = m_Registers.A - FetchByte(ram, m_Registers.HL);
            m_Registers.ZF = data == 0;
            m_Registers.NF = 1;
            m_Registers.HF = GET_BIT(data, 3);
            m_Registers.CF = GET_BIT(data, 7);

            m_Cycles += 2;
            break;
        }
        case INS_JP_8:
        {
            m_Registers.PC = FetchWord(ram, m_Registers.PC);
            m_Cycles += 4;
            break;
        }
        case INS_CALL_16:
        {
            U16 data = FetchWord(ram, m_Registers.PC);

            m_Registers.SP--;
            WriteWord(ram, m_Registers.SP, m_Registers.PC);
            m_Registers.SP--;

            m_Registers.PC = data;
            m_Cycles += 6;
            break;
        }
    }
#if defined(GBE_DEBUG)
    if (m_DebugArguments.size() == 1)
    {
        std::printf("%s\n", ConvertToASM(instruction).c_str());
    }
    else
    {
        std::printf("%s\n", std::vformat(ConvertToASM(instruction), std::make_format_args(m_DebugArguments[1])).c_str());
    }
#endif
}

U8 CPU::FetchByte(const RAM& ram, U16 address)
{
    const U8 data = ram[address];

#if defined(GBE_DEBUG)
    m_DebugArguments.emplace_back(data);
#endif

    return data;
}
U16 CPU::FetchWord(const RAM& ram, U16 address)
{
    U16 data = ram[address] & 0xff;
    data |= ram[address + 1] << 8;

#if defined(GBE_DEBUG)
    m_DebugArguments.emplace_back(data);
#endif

    return data;
}

void CPU::WriteByte(RAM& ram, U16 address, U8 data)
{
    ram[address] = data;

#if defined(GBE_DEBUG)
    m_DebugArguments.emplace_back(data);
#endif
}

void CPU::WriteWord(RAM& ram, U16 address, U16 data)
{
    ram[address] = ~(data | 0x00FF);
    ram[address - 1] = ~(data | 0xFF00);

#if defined(GBE_DEBUG)
    m_DebugArguments.emplace_back(data);
#endif
}

const std::string CPU::ConvertToASM(U8 instruction) const
{
    switch (instruction)
    {
        case INS_NOP:
            return "NOP";
        case INS_DEC_B:
            return "DEC B";
        case INS_DEC_C:
            return "DEC C";
        case INS_DEC_D:
            return "DEC D";
        case INS_DEC_E:;
            return "DEC E";
        case INS_DEC_H:
            return "DEC H";
        case INS_DEC_L:
            return "DEC L";
        case INS_DEC_HL:
            return "DEC [HL]";
        case INS_DEC_A:
            return "DEC A";
        case INS_INC_B:
            return "INC B";
        case INS_INC_C:
            return "INC C";
        case INS_INC_D:
            return "INC D";
        case INS_INC_E:
            return "INC E";
        case INS_INC_H:
            return "INC H";
        case INS_INC_L:
            return "INC L";
        case INS_INC_HL:
            return "INC [HL]";
        case INS_INC_A:
            return "INC A";
        case INS_LD_B_8:
            return "LD B, {:#x}";
        case INS_LD_C_8:
            return "LD C, {:#x}";
        case INS_LD_HL_NEG_A:
            return "LD [HL-], A";
        case INS_LD_A_HL_POS:
            return "LD A, [HL+]";
        case INS_LD_BC_16:
            return "LD BC, {:#x}";
        case INS_LD_DE_16:
            return "LD DE, {:#x}";
        case INS_LD_HL_16:
            return "LD HL, {:#x}";
        case INS_LD_SP_16:
            return "LD SP, {:#x}";
        case INS_LDH_C_A:
            return "LDH [C], A";
        case INS_XOR_A_A:
            return "XOR A, A";
        case INS_CP_A_HL:
            return "CP A, [HL]";
        case INS_JR_NZ_8:
            return "JR NZ, {:#x}";
        case INS_JP_8:
            return "JP {:#x}";
        case INS_CALL_16:
            return "CALL {:#x}";
        default:
            return std::format("{:#x} is currently not implemented!", instruction);
    }
}

void CPU::DEC_r_8(U8& reg)
{
    reg--;
    m_Registers.ZF = reg == 0;
    m_Registers.NF = 1;
    m_Registers.HF = GET_BIT(reg, 3);
    m_Cycles++;
}

void CPU::INC_r_8(U8& reg)
{
    reg++;
    m_Registers.ZF = reg == 0;
    m_Registers.NF = 0;
    m_Registers.HF = GET_BIT(reg, 3);
    m_Cycles++;
}

void CPU::LD_rr_16(const RAM& ram, U16& reg)
{
    reg = FetchWord(ram, m_Registers.PC);
    m_Registers.PC += 2;
    m_Cycles += 3;
}
} // namespace Emulator
