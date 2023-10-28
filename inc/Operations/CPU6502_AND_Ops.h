#pragma once
#include "CPU6502.h"

inline void ExecuteAND(CPU6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDY(Memory &memory, CPU6502 &cpu);
