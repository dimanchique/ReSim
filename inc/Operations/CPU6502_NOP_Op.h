#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_NOP_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
