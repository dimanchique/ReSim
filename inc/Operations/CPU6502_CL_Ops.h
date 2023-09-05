#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CLC_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_CLD_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_CLI_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_CLV_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU);
