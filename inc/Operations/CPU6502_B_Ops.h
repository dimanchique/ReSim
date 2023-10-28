#pragma once
#include "CPU6502.h"

inline void ExecuteB(Memory &memory, CPU6502 &cpu, const BYTE targetFlag, const bool expectedValue) {
    const SBYTE Offset = cpu.FetchByte(memory);
    if (targetFlag == expectedValue) {
        cpu.cycles++;
        if (IsPageCrossed(cpu.PC, cpu.PC + Offset))
            cpu.cycles++;
        cpu.PC += Offset;
    }
}

void CPU6502_BCC_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BCS_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BEQ_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BNE_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BMI_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BPL_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BVC_REL(Memory &memory, CPU6502 &cpu);
void CPU6502_BVS_REL(Memory &memory, CPU6502 &cpu);
