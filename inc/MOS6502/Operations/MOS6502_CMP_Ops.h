#pragma once

#include "MOS6502_CM_Ops.h"

/**
 * @instruction Compare Accumulator – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_IM(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_IM(memory, cpu, cpu.A);
}

/**
 * @instruction Compare Accumulator – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ZP(memory, cpu, cpu.A);
}

/**
 * @instruction Compare Accumulator – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ZPX(memory, cpu, cpu.A);
}

/**
 * @instruction Compare Accumulator – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ABS(memory, cpu, cpu.A);
}

/**
 * @instruction Compare Accumulator – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ABS(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Compare Accumulator – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_CM_ABS(memory, cpu, cpu.A, cpu.Y);
}

/**
 * @instruction Compare Accumulator – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericCM(cpu, cpu.A, value);
}

/**
 * @instruction Compare Accumulator – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_CMP_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericCM(cpu, cpu.A, value);
}
