#pragma once
#include "MOS6502.h"

/**
 * @brief Set Flag Implementation
 * @details Set the target flag to one.
 * @param cpu MOS6502 struct instance.
 * @param statusFlag Status flag to set.
 */
FORCE_INLINE void GenericSE(MOS6502 &cpu, const BYTE statusFlag) {
    cpu.Status.Value |= statusFlag;
    ++cpu.cycles;
}

/**
 * @brief Set Carry Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SEC_IMPL(MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_C);
}

/**
 * @brief Set Decimal Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SED_IMPL(MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_D);
}

/**
 * @brief Set Interrupt Disable Flag
 * @addressing Implied
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SEI_IMPL(MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_I);
}
