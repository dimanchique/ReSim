#pragma once
#include "CPU6502.h"

inline void ExecuteDEC(Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    memoryValue--;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEC_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_DEX_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_DEY_IMPL(Memory &memory, CPU6502 &cpu);
