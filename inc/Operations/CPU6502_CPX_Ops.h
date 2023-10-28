#pragma once
#include "CPU6502_CM_Ops.h"

/**
 * @instruction Compare register X
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CPX_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(memory, cpu, cpu.X);
}

/**
 * @instruction Compare register X
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CPX_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.X);
}

/**
 * @instruction Compare register X
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
inline void CPU6502_CPX_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.X);
}

