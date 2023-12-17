#pragma once

#include "MOS6502.h"

/**
 * @instruction Push Accumulator – Implied
 * @details Pushes a copy of the accumulator on to the stack.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_PHA_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.PushByteToStack(memory, cpu.A);
}

/**
 * @instruction Pull Accumulator – Implied
 * @details Pulls an 8 bit value from the stack and into the accumulator.
 * The zero and negative flags are set as appropriate.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_PLA_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.A = cpu.PopByteFromStack(memory);
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Push Processor Status – Implied
 * @details Pushes a copy of the status flags on to the stack.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_PHP_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.PushStatusToStack(memory);
}

/**
 * @instruction Pull Processor Status – Implied
 * @details Pulls an 8 bit value from the stack and into the processor flags.
 * The flags will take on new states as determined by the value pulled.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_PLP_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.PopStatusFromStack(memory);
}
