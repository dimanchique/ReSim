#pragma once
#include "CPU6502.h"

inline void ExecuteAND(CPU6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
