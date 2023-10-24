#pragma once
#include "CPU6502.h"

inline void ExecuteINC(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    memoryValue++;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
