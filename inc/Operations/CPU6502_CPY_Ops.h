#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CPY_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_CPY_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_CPY_ABS(Memory &memory, CPU6502 &cpu);
