#pragma once

#include "MOS6502_LD_Ops.h"

/**
 * @instruction Load X Register – Immediate
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDX_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_IM(memory, cpu, cpu.X);
}

/**
 * @instruction Load X Register – Zero Page
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDX_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.X);
}

/**
 * @instruction Load X Register – Zero Page,Y
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDX_ZPY(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.X, cpu.Y);
}

/**
 * @instruction Load X Register – Absolute
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDX_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.X);
}

/**
 * @instruction Load X Register – Absolute,Y
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDX_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.X, cpu.Y);
}
