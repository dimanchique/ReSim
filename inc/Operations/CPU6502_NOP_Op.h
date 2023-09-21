#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_NOP_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU);
