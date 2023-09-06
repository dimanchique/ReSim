#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_PHA_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PLA_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PHP_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_PLP_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
