#pragma once
#include "CPU6502.h"

/**
 * @instruction Logical Shift Right (generic)
 * @description
 * Each of the bits in A or M is shift one place to the right.
 * The bit that was in bit 0 is shifted into the carry flag.
 * Bit 7 is set to zero.
 * @short A,C,Z,N = A/2 or M,C,Z,N = M/2
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param memoryValue Value to shift
 * @param address Address to write back shifted value
 */
inline void GenericLSR(Memory &memory, CPU6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

/**
 * @instruction Logical Shift Right Accumulator
 * @description
 * Same as GenericLSR, but with Accumulator as target
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LSR_ACC(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Shift Right
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LSR_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Shift Right
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LSR_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Shift Right
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LSR_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Shift Right
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LSR_ABSX(Memory &memory, CPU6502 &cpu);
