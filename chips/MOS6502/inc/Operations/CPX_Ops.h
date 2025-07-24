#pragma once
#include "CM_Ops.h"

/**
 * @brief Compare register X
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_IM(MOS6502 &cpu) {
    PerformCPX(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Compare register X
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_ZP(MOS6502 &cpu) {
    PerformCPX(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Compare register X
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_CPX_ABS(MOS6502 &cpu) {
    PerformCPX(cpu, MOS6502_AddressingMode::Absolute);
}
