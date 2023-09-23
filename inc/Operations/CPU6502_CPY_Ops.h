#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CPY_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CPY_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CPY_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
