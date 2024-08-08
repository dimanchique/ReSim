#pragma once
#include "CM_Ops.h"

/**
 * @instruction Compare register X – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CPX_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_IM(memory, cpu, cpu.X);
}

/**
 * @instruction Compare register X – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CPX_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ZP(memory, cpu, cpu.X);
}

/**
 * @instruction Compare register X – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CPX_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ABS(memory, cpu, cpu.X);
}

