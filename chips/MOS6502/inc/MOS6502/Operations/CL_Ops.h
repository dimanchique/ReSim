#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Clear Flag Implementation
 * @details Clear target status flag.
 * @param cpu MOS6502 struct instance.
 * @param statusFlag Status flag to clear.
 */
FORCE_INLINE void PerformCL(MOS6502 &cpu, const BYTE statusFlag) {
    cpu.Status.Value &= ~statusFlag;
    cpu.cycles++;
}

/**
 * @brief Clear Carry Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLC_IMPL(MOS6502 &cpu) {
    PerformCL(cpu, MOS6502_Status_C);
}

/**
 * @brief Clear Decimal Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLD_IMPL(MOS6502 &cpu) {
    PerformCL(cpu, MOS6502_Status_D);
}

/**
 * @brief Clear Interrupt Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLI_IMPL(MOS6502 &cpu) {
    PerformCL(cpu, MOS6502_Status_I);
}

/**
 * @brief Clear Overflow Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLV_IMPL(MOS6502 &cpu) {
    PerformCL(cpu, MOS6502_Status_V);
}
