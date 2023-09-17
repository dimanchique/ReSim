#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_INC_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_INC_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_INC_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_INC_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_INX_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_INY_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
