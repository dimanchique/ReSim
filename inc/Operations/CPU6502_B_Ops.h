#pragma once
#include "CPU6502.h"

inline void ExecuteB(U32 &cycles, Memory &memory, CPU6502 &cpu, const BYTE targetFlag, const bool expectedValue) {
    const SBYTE Offset = cpu.FetchByte(cycles, memory);
    if (targetFlag == expectedValue) {
        CPU6502::DoTick(cycles);
        if (CPU6502::IsPageCrossed(cpu.PC, cpu.PC + Offset))
            CPU6502::DoTick(cycles);
        cpu.PC += Offset;
    }
}

void CPU6502_BCC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BCS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BEQ_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BNE_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BMI_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BPL_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BVC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BVS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
