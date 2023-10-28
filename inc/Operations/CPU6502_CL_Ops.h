#pragma once
#include "CPU6502.h"

/**
 * @instruction Clear Flag (generic)
 * @description
 * Clear target status flag.
 * @param cpu CPU6502 struct instance
 * @param statusFlag Status flag to clear
 */
inline void GenericCL(CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, false);
    cpu.cycles++;
}

/**
 * @instruction Clear Carry Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CLC_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericCL(cpu, CPU6502_Status_C);
}

/**
 * @instruction Clear Decimal Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CLD_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericCL(cpu, CPU6502_Status_D);
}

/**
 * @instruction Clear Interrupt Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CLI_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericCL(cpu, CPU6502_Status_I);
}

/**
 * @instruction Clear Overflow Flag
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CLV_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericCL(cpu, CPU6502_Status_V);
}
