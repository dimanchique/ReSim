#pragma once
#include "CPU6502.h"

/**
 * @instruction Rotate Right (generic)
 * @description
 * Move each of the bits in either A or M one place to the right.
 * Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new carry flag value.
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param memoryValue Value to rotate
 * @param address Address to write back shifted value
 */
inline void GenericROR(Memory &memory, CPU6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Rotate Right Accumulator
 * @description
 * Same as GenericROR, but with Accumulator as target
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROR_ACC(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Right
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROR_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Right
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROR_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Right
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROR_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Right
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROR_ABSX(Memory &memory, CPU6502 &cpu);
