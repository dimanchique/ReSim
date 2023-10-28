#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CPX_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_CPX_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_CPX_ABS(Memory &memory, CPU6502 &cpu);
