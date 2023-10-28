#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_PHA_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_PLA_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_PHP_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_PLP_IMPL(Memory &memory, CPU6502 &cpu);
