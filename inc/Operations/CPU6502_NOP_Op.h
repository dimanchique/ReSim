#pragma once
#include "CPU6502.h"

inline void CPU6502_NOP_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.cycles++;
}
