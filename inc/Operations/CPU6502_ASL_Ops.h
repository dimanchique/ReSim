#pragma once
#include "CPU6502.h"

/**
 * @instruction Arithmetic Shift Left (generic)
 * @description
 * This operation shifts all the bits of the accumulator or memory contents one bit left.
 * Bit 0 is set to 0 and bit 7 is placed in the carry flag.
 * The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations), setting the carry if the result will not fit in 8 bits.
 * @short A,Z,C,N = M*2 or M,Z,C,N = M*2
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param memoryValue Value to shift
 * @param address Address to write back shifted value
 */
inline void GenericASL(Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    const bool Carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Arithmetic Shift Left Accumulator
 * @description
 * Same as GenericASL, but with Accumulator as target
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ASL_ACC(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ASL_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ASL_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ASL_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ASL_ABSX(Memory &memory, CPU6502 &cpu);
