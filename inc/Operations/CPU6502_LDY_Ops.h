#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDY_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_LDY_ABSX(Memory &memory, CPU6502 &cpu);
