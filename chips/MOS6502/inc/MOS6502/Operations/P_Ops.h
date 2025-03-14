#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Push Accumulator
 * @addressing Implied
 * @details Pushes a copy of the accumulator on to the stack.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_PHA_IMPL(MOS6502 &cpu) {
    cpu.PushByteToStack(cpu.A);
}

/**
 * @brief Pull Accumulator
 * @addressing Implied
 * @details Pulls an 8 bit value from the stack and into the accumulator.
 * The zero and negative flags are set as appropriate.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_PLA_IMPL(MOS6502 &cpu) {
    cpu.A = cpu.PopByteFromStack();
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Push Processor Status
 * @addressing Implied
 * @details Pushes a copy of the status flags on to the stack.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_PHP_IMPL(MOS6502 &cpu) {
    cpu.PushStatusToStack();
}

/**
 * @brief Pull Processor Status
 * @addressing Implied
 * @details Pulls an 8 bit value from the stack and into the processor flags.
 * The flags will take on new states as determined by the value pulled.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_PLP_IMPL(MOS6502 &cpu) {
    cpu.PopStatusFromStack();
}
