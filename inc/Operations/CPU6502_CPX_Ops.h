#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CPX_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CPX_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CPX_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
