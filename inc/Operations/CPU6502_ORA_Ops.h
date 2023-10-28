#pragma once
#include "CPU6502.h"

inline void ExecuteORA(CPU6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_ORA_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDY(Memory &memory, CPU6502 &cpu);
