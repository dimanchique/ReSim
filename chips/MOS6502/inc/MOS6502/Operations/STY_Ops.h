#pragma once
#include "ST_Ops.h"

/**
 * @instruction Store Y Register – Zero Page
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STY_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.Y);
}

/**
 * @instruction Store Y Register – Zero Page,X
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STY_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.Y, cpu.X);
}

/**
 * @instruction Store Y Register – Absolute
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STY_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.Y);
}
