#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_DEC_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEX_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEY_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
