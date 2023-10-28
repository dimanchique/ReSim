#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDX_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ZPY(Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_LDX_ABSY(Memory &memory, CPU6502 &cpu);
