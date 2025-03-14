#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief No Operation Implementation
 * @details The NOP instruction causes no changes to the processor
 * other than the normal incrementing of the program counter to the next instruction.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_NOP_IMPL(MOS6502 &cpu) {
    cpu.cycles++;
}
