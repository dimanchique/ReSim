#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STX_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ZPY(Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ABS(Memory &memory, CPU6502 &cpu);
