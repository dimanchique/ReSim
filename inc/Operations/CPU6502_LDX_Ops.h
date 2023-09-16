#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDX_IM(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZPY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABSY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
