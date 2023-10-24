#pragma once
#include "CPU6502.h"

inline void ExecuteDEC(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    memoryValue--;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
