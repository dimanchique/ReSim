#pragma once
#include "ST_Ops.h"

/**
 * @brief Store Accumulator
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZP(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Store Accumulator
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZPX(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABS(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSX(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::Absolute_X, false);
}

/**
 * @brief Store Accumulator
 * @addressing Absolute,Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABSY(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::Absolute_Y, false);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect,X)
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDX(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Store Accumulator
 * @addressing (Indirect),Y
 * @todo fix cycles count mismatch
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDY(MOS6502 &cpu) {
    PerformSTA(cpu, MOS6502_AddressingMode::Indirect_Y, false);
    cpu.cycles++; // extra cycle required
}
