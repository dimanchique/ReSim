#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STY_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ABS(Memory &memory, CPU6502 &cpu);
