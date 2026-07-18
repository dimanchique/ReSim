#pragma once
#include "MOS6502.h"

/**
 * @brief Logical Shift Right Implementation
 * @details Each of the bits in A or M is shifted one place to the right.
 * The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
 * @short A,C,Z,N = A/2 or M,C,Z,N = M/2
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformLSR(MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const WORD address = cpu.GetAddressingModeAddress(addressing, shouldCheckPageCross);

    BYTE memoryValue = cpu.ReadByte(address);
    const bool carry = memoryValue & 1;
    memoryValue >>= 1;
    ++cpu.cycles;
    cpu.WriteByte(memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Logical Shift Right Accumulator
 * @details Same as PerformLSR, but with Accumulator as target.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ACC(MOS6502 &cpu) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    ++cpu.cycles;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @brief Logical Shift Right
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ZP(MOS6502 &cpu) {
    PerformLSR(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Logical Shift Right
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ZPX(MOS6502 &cpu) {
    PerformLSR(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Logical Shift Right
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ABS(MOS6502 &cpu) {
    PerformLSR(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Logical Shift Right
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LSR_ABSX(MOS6502 &cpu) {
    PerformLSR(cpu, MOS6502_AddressingMode::Absolute_X, false);
}
