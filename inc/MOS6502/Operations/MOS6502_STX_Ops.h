#pragma once

#include "MOS6502_ST_Ops.h"

/**
 * @instruction Store X Register – Zero Page
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STX_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.X);
}

/**
 * @instruction Store X Register – Zero Page,Y
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STX_ZPY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.X, cpu.Y);
}

/**
 * @instruction Store X Register – Absolute
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STX_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.X);
}
