#pragma once
#include "CPU6502.h"

inline void ExecuteROR(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
