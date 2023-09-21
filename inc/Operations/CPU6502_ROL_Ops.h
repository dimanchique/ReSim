#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_ROL_ACC(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ZPX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ROL_ABSX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
