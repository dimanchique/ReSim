#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare register Y
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_IM(MOS6502 &cpu) {
    PerformCPY(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Compare register Y
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_ZP(MOS6502 &cpu) {
    PerformCPY(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Compare register Y
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPY_ABS(MOS6502 &cpu) {
    PerformCPY(cpu, MOS6502_AddressingMode::Absolute);
}
