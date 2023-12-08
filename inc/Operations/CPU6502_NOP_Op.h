#pragma once
#include "CPU6502.h"

/**
 * @instruction No Operation
 * @details The NOP instruction causes no changes to the processor
 * other than the normal incrementing of the program counter to the next instruction.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
FORCE_INLINE void CPU6502_NOP_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.cycles++;
}
