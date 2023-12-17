#pragma once

#include "MOS6502_ST_Ops.h"

/**
 * @instruction Store Accumulator – Zero Page
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A);
}

/**
 * @instruction Store Accumulator – Zero Page,X
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Store Accumulator – Absolute
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_ABS(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A);
}

/**
 * @instruction Store Accumulator
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Store Accumulator
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ABS(memory, cpu, cpu.A, cpu.Y);
}

/**
 * @instruction Store Accumulator
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_INDX(Memory &memory, MOS6502 &cpu) {
    const WORD TargetAddress = cpu.GetIndXAddress(memory);
    cpu.WriteByte(memory, cpu.A, TargetAddress);
}

/**
 * @instruction Store Accumulator
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_STA_INDY(Memory &memory, MOS6502 &cpu) {
    const WORD TargetAddress = cpu.GetIndYAddress(memory);
    cpu.WriteByte(memory, cpu.A, TargetAddress);
    cpu.cycles++; // extra cycle required
}
