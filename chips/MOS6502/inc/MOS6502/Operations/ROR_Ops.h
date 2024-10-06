#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Rotate Right (generic)
 * @details Move each of the bits in either A or M one place to the right.
 * Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new carry flag value.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param memoryValue Value to rotate.
 * @param address Address to write back shifted value.
 */
FORCE_INLINE void GenericROR(Memory &memory, MOS6502 &cpu, const WORD address) {
    BYTE memoryValue = cpu.ReadByte(memory, address);
    const bool carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @instruction Rotate Right Accumulator
 * @details Same as GenericROR, but with Accumulator as target.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ROR_ACC(Memory &memory, MOS6502 &cpu) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= cpu.Status.C << 7;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = carry;
}

/**
 * @instruction Rotate Right – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ROR_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericROR(memory, cpu, address);
}

/**
 * @instruction Rotate Right – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ROR_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericROR(memory, cpu, address);
}

/**
 * @instruction Rotate Right – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ROR_ABS(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericROR(memory, cpu, address);
}

/**
 * @instruction Rotate Right – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ROR_ABSX(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericROR(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}