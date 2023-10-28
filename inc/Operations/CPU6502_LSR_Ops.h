#pragma once
#include "CPU6502.h"

inline void ExecuteLSR(Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_LSR_ACC(Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ABSX(Memory &memory, CPU6502 &cpu);
