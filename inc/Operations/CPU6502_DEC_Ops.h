#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_DEC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_DEY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
