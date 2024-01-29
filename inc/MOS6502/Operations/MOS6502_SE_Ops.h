#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Set Flag (generic)
 * @details Set the target flag to one.
 * @param cpu MOS6502 struct instance.
 * @param statusFlag Status flag to set.
 */
FORCE_INLINE void GenericSE(MOS6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, true);
    cpu.cycles++;
}

/**
 * @instruction Set Carry Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SEC_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_C);
}

/**
 * @instruction Set Decimal Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SED_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_D);
}

/**
 * @instruction Set Interrupt Disable Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SEI_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericSE(cpu, MOS6502_Status_I);
}
