#pragma once
#include "CPU6502.h"

inline void ExecuteBIT(CPU6502 &cpu, const BYTE mask) {
    const BYTE value = cpu.A & mask;
    cpu.Status.Z = value == 0;
    cpu.Status.V = (mask >> 6) & 1;
    cpu.Status.N = (mask >> 7) & 1;
}

void CPU6502_BIT_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_BIT_ABS(Memory &memory, CPU6502 &cpu);
