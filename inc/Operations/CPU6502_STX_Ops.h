#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STX_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ZPY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STX_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
