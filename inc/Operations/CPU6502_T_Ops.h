#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_TAX_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXA_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TAY_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TYA_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TSX_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXS_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
