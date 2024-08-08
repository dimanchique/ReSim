#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Arithmetic Shift Left (generic)
 * @details This operation shifts all the bits of the accumulator or memory contents one bit left.
 * Bit 0 is set to 0 and bit 7 is placed in the carry flag.
 * The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations),
 * setting the carry if the result will not fit in 8 bits.
 * @short A,Z,C,N = M*2 or M,Z,C,N = M*2
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param memoryValue Value to shift.
 * @param address Address to write back shifted value.
 */
FORCE_INLINE void GenericASL(Memory &memory, MOS6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    const bool Carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Arithmetic Shift Left Accumulator
 * @details Same as GenericASL, but with Accumulator as target.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ASL_ACC(Memory &memory, MOS6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Arithmetic Shift Left – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ASL_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericASL(memory, cpu, address);
}

/**
 * @instruction Arithmetic Shift Left – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ASL_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericASL(memory, cpu, address);
}

/**
 * @instruction Arithmetic Shift Left – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ASL_ABS(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericASL(memory, cpu, address);
}

/**
 * @instruction Arithmetic Shift Left – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ASL_ABSX(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericASL(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}
