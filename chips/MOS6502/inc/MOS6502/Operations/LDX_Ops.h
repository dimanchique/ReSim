#pragma once
#include "LD_Ops.h"

/**
 * @brief Load X Register
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_IM(MOS6502 &cpu) {
    PerformLDX(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Load X Register
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ZP(MOS6502 &cpu) {
    PerformLDX(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Load X Register
 * @addressing Zero Page,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ZPY(MOS6502 &cpu) {
    PerformLDX(cpu, MOS6502_AddressingMode::ZeroPage_Y);
}

/**
 * @brief Load X Register
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ABS(MOS6502 &cpu) {
    PerformLDX(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Load X Register
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDX_ABSY(MOS6502 &cpu) {
    PerformLDX(cpu, MOS6502_AddressingMode::Absolute_Y);
}
