#pragma once
#include "CPU6502.h"

inline void ExecuteINC(Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    memoryValue++;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INC_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_INX_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_INY_IMPL(Memory &memory, CPU6502 &cpu);
