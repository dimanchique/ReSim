#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LSR_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LSR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
