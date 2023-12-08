#pragma once
#include "CPU6502_ST_Ops.h"

/**
 * @instruction Store Y Register – Zero Page
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STY_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.Y);
}

/**
 * @instruction Store Y Register – Zero Page,X
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STY_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.Y, cpu.X);
}

/**
 * @instruction Store Y Register – Absolute
 * @details Stores the contents of the Y register into memory.
 * @short M = Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STY_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.Y);
}
