#pragma once
#include "CPU6502.h"

inline void ExecuteEOR(CPU6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDY(Memory &memory, CPU6502 &cpu);
