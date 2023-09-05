#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_JMP_ABS(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_JMP_IND(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_JSR_ABS(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_RTS_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_RTI_IMPL(S32& cycles, Memory &memory, CPU6502 &cpu);
