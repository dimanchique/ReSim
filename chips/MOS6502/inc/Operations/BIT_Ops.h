#pragma once
#include "MOS6502.h"

/**
 * @brief Bit Test Implementation
 * @details This instructions is used to test if one or more bits are set in a target memory location.
 * The mask pattern in A is ANDed with the value in memory to set or clear the zero flag, but the result is not kept.
 * Bits 7 and 6 of the value from memory are copied into the N and V flags.
 * @short A & M, N = M7, V = M6
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformBIT(MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE mask = cpu.GetAddressingModeValue(addressing);

    const BYTE value = cpu.A & mask;
    cpu.Status.Z = value == 0;
    cpu.Status.V = (mask & MOS6502_Status_V) > 0;
    cpu.Status.N = (mask & MOS6502_Status_N) > 0;
}

/**
 * @brief Bit Test
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BIT_ZP(MOS6502 &cpu) {
    PerformBIT(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Bit Test
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BIT_ABS(MOS6502 &cpu) {
    PerformBIT(cpu, MOS6502_AddressingMode::Absolute);
}
