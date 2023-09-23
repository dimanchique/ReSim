#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STY_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STY_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
