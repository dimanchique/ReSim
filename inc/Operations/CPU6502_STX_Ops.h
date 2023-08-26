#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STX_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ZPY(S32& Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu);
