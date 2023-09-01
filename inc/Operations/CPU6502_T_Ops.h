#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_TAX_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXA_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TAY_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TYA_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TSX_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXS_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
