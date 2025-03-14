#pragma once
#include "LD_Ops.h"

/**
 * @brief Load Y Register
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_IM(MOS6502 &cpu) {
    PerformLDY(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZP(MOS6502 &cpu) {
    PerformLDY(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Load Y Register
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ZPX(MOS6502 &cpu) {
    PerformLDY(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Load Y Register
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABS(MOS6502 &cpu) {
    PerformLDY(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Load Y Register
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDY_ABSX(MOS6502 &cpu) {
    PerformLDY(cpu, MOS6502_AddressingMode::Absolute_X);
}
