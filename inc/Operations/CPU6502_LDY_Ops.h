#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDY_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
