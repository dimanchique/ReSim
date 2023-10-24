#pragma once
#include "CPU6502.h"

inline void ExecuteEOR(CPU6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
