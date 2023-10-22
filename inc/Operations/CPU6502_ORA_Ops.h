#pragma once
#include "CPU6502.h"

inline void ExecuteORA(CPU6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_ORA_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
