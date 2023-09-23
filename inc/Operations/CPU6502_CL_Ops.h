#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CLC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLD_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CLV_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
