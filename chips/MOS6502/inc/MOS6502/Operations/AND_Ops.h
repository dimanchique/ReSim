#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical AND Implementation
 * @details A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A&M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformAND(MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(addressing);

    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Logical AND
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_IM(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Logical AND
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZP(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Logical AND
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZPX(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Logical AND
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABS(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Logical AND
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSX(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Logical AND
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSY(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Logical AND
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDX(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Logical AND
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDY(MOS6502 &cpu) {
    PerformAND(cpu, MOS6502_AddressingMode::Indirect_Y);
}
