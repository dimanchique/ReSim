#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STY_ZP(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ZPX(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ABS(S32& cycles, Memory &memory, CPU6502 &cpu);
