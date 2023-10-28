#pragma once
#include "CPU6502.h"

inline void ExecuteSBC(CPU6502 &cpu, const BYTE Operand) {
    const bool AreSignBitsTheSame = !((cpu.A ^ Operand) & CPU6502_Status_N);
    const WORD Sub = cpu.A - Operand - (1 - cpu.Status.C);
    cpu.A = Sub;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sub > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ Operand) & CPU6502_Status_N));
}

void CPU6502_SBC_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_INDY(Memory &memory, CPU6502 &cpu);
