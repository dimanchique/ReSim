#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_SEC_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_SED_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
void CPU6502_SEI_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
