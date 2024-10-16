#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Clear Flag (generic)
 * @details Clear target status flag.
 * @param cpu MOS6502 struct instance.
 * @param statusFlag Status flag to clear.
 */
FORCE_INLINE void GenericCL(MOS6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, false);
    cpu.cycles++;
}

/**
 * @instruction Clear Carry Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLC_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericCL(cpu, MOS6502_Status_C);
}

/**
 * @instruction Clear Decimal Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLD_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericCL(cpu, MOS6502_Status_D);
}

/**
 * @instruction Clear Interrupt Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLI_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericCL(cpu, MOS6502_Status_I);
}

/**
 * @instruction Clear Overflow Flag – Implied
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CLV_IMPL(Memory &memory, MOS6502 &cpu) {
    GenericCL(cpu, MOS6502_Status_V);
}
