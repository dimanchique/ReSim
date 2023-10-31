#pragma once
#include "CPU6502_CM_Ops.h"

/**
 * @instruction Compare register Y – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_CPY_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(memory, cpu, cpu.Y);
}

/**
 * @instruction Compare register Y – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_CPY_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.Y);
}

/**
 * @instruction Compare register Y – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_CPY_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.Y);
}
