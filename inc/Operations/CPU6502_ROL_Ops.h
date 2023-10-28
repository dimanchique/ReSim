#pragma once
#include "CPU6502.h"

inline void ExecuteROL(Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    const bool Carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    memoryValue |= cpu.Status.C;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROL_ACC(Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ABSX(Memory &memory, CPU6502 &cpu);
