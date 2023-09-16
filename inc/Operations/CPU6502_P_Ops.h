#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_PHA_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PLA_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PHP_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PLP_IMPL(U32 &Cycles, Memory &memory, CPU6502 &cpu);
