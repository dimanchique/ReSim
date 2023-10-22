#pragma once
#include "CPU6502.h"

inline void CPU6502_NOP_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502::DoTick(cycles);
}
