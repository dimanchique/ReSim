#pragma once
#include "MOS6502_LD_Ops.h"

/**
 * @instruction Load Y Register – Immediate
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDY_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_IM(memory, cpu, cpu.Y);
}

/**
 * @instruction Load Y Register – Zero Page
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDY_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.Y);
}

/**
 * @instruction Load Y Register – Zero Page,X
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDY_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ZP(memory, cpu, cpu.Y, cpu.X);
}

/**
 * @instruction Load Y Register – Absolute
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDY_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.Y);
}

/**
 * @instruction Load Y Register – Absolute,X
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_LDY_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_LD_ABS(memory, cpu, cpu.Y, cpu.X);
}
