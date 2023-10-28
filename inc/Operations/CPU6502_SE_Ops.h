#pragma once
#include "CPU6502.h"

/**
 * @instruction Set Flag (generic)
 * @description
 * Set the target flag to one.
 * @param cpu CPU6502 struct instance
 * @param statusFlag Status flag to set
 */
inline void GenericSE(CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, true);
    cpu.cycles++;
}

/**
 * @instruction Set Carry Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_SEC_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericSE(cpu, CPU6502_Status_C);
}

/**
 * @instruction Set Decimal Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_SED_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericSE(cpu, CPU6502_Status_D);
}

/**
 * @instruction Set Interrupt Disable Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_SEI_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericSE(cpu, CPU6502_Status_I);
}
