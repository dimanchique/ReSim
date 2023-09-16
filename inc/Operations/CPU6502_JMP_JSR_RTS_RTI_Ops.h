#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_JMP_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_JMP_IND(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_JSR_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_RTS_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_RTI_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
