#pragma once
#include "ST_Ops.h"

/**
 * @instruction Store Accumulator – Zero Page
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZP(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A);
}

/**
 * @instruction Store Accumulator – Zero Page,X
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ZPX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ST_ZP(memory, cpu, cpu.A, cpu.X);
}

/**
 * @instruction Store Accumulator – Absolute
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_ABS(Memory &memory, MOS6502 &cpu) {
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
void MOS6502_STA_ABSX(Memory &memory, MOS6502 &cpu) {
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
void MOS6502_STA_ABSY(Memory &memory, MOS6502 &cpu) {
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
void MOS6502_STA_INDX(Memory &memory, MOS6502 &cpu) {
    const WORD targetAddress = cpu.GetIndXAddress(memory);
    cpu.WriteByte(memory, cpu.A, targetAddress);
}

/**
 * @instruction Store Accumulator
 * @details Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_STA_INDY(Memory &memory, MOS6502 &cpu) {
    const WORD targetAddress = cpu.GetIndYAddress(memory, false);
    cpu.WriteByte(memory, cpu.A, targetAddress);
    cpu.cycles++; // extra cycle required
}
