#pragma once
#include "CPU6502_ST_Ops.h"

/**
 * @instruction Store X Register – Zero Page
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STX_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.X);
}

/**
 * @instruction Store X Register – Zero Page,Y
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STX_ZPY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.X, cpu.Y);
}

/**
 * @instruction Store X Register – Absolute
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_STX_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.X);
}
