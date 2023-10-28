#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_JMP_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_JMP_IND(Memory &memory, CPU6502 &cpu);
void CPU6502_JSR_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_RTS_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_RTI_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_BRK_IMPL(Memory &memory, CPU6502 &cpu);
