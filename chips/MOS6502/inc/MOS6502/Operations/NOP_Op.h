#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction No Operation
 * @details The NOP instruction causes no changes to the processor
 * other than the normal incrementing of the program counter to the next instruction.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_NOP_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.cycles++;
}
