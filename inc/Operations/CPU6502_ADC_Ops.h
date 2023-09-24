#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void ExecuteADC(CPU6502 &cpu, BYTE value);

void CPU6502_ADC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ADC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
