#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare Accumulator
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_IM(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Compare Accumulator
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ZP(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Compare Accumulator
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ZPX(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABS(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABSX(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Compare Accumulator
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_ABSY(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Compare Accumulator
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_INDX(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Compare Accumulator
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CMP_INDY(MOS6502 &cpu) {
    PerformCMP(cpu, MOS6502_AddressingMode::Indirect_Y);
}
