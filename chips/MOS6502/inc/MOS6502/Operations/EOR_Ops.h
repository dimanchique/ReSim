#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Exclusive OR Implementation
 * @details An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A^M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformEOR(MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
    const BYTE value = cpu.GetAddressingModeValue(addressing, shouldCheckPageCross);

    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Exclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_IM(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Exclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ZP(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Exclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ZPX(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABS(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABSX(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Exclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_ABSY(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Exclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_INDX(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Exclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_EOR_INDY(MOS6502 &cpu) {
    PerformEOR(cpu, MOS6502_AddressingMode::Indirect_Y, false);
}
