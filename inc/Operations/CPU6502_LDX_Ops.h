#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDX_IM(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZPY(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu);
