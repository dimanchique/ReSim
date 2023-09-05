#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_DEC_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ZPX(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEC_ABSX(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_DEY_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
