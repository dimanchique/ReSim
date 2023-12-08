#pragma once
#include "CPU6502_LD_Ops.h"

/**
 * @instruction Load Accumulator – Immediate
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(memory, cpu, cpu.A);
}

/**
 * @instruction Load Accumulator – Zero Page
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.A);
}

/**
 * @instruction Load Accumulator – Zero Page,X
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Load Accumulator – Absolute
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A);
}

/**
 * @instruction Load Accumulator – Absolute,X
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Load Accumulator – Absolute,Y
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A, cpu.Y);
}

/**
 * @instruction Load Accumulator – (Indirect,X)
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    GenericLD(cpu, cpu.A, Data);
}

/**
 * @instruction Load Accumulator – (Indirect),Y
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_LDA_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    GenericLD(cpu, cpu.A, Data);
}
