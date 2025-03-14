#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Logical Inclusive OR Implementation
 * @details An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A|M
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformORA(MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(addressing);

    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_IM(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZP(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZPX(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABS(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSX(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing Absolute,Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSY(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect,X)
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDX(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Logical Inclusive OR
 * @addressing (Indirect),Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDY(MOS6502 &cpu) {
    PerformORA(cpu, MOS6502_AddressingMode::Indirect_Y);
}
