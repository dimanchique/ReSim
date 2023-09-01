#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDY_IM(S32&   cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZP(S32&   cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZPX(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABS(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABSX(S32& cycles, Memory &memory, CPU6502 &cpu);
