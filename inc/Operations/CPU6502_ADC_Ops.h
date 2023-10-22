#pragma once
#include "CPU6502.h"

inline void ExecuteADC(CPU6502 &cpu, const BYTE value) {
    const bool AreSignBitsTheSame = !((cpu.A ^ value) & CPU6502_Status_N);
    const WORD Sum = cpu.A + value + cpu.Status.C;
    cpu.A = Sum;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sum > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ value) & CPU6502_Status_N));
}

void CPU6502_ADC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
