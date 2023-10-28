#pragma once
#include "CPU6502.h"

/**
 * @instruction Rotate Left (generic)
 * @description
 * Move each of the bits in either A or M one place to the left.
 * Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param memoryValue Value to rotate
 * @param address Address to write back shifted value
 */
inline void GenericROL(Memory &memory, CPU6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    const bool Carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    memoryValue |= cpu.Status.C;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Rotate Left Accumulator
 * @description
 * Same as GenericROL, but with Accumulator as target
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROL_ACC(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Left
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROL_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Left
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROL_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Left
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROL_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Rotate Left
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ROL_ABSX(Memory &memory, CPU6502 &cpu);
