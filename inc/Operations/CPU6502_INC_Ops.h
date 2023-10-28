#pragma once
#include "CPU6502.h"

/**
 * @instruction Increment Memory (generic)
 * @description
 * Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
 * @short M,Z,N = M+1
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @param memoryValue Memory value to increment
 * @param address Address to write back modified value
 */
inline void GenericINC(Memory &memory, CPU6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    memoryValue++;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

/**
 * @instruction Increment Memory
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INC_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Increment Memory
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INC_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Increment Memory
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INC_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Increment Memory
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INC_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Increment X Register
 * @addressing Implied
 * @short X,Z,N = X+1
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INX_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Increment Y Register
 * @addressing Implied
 * @short Y,Z,N = Y+1
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_INY_IMPL(Memory &memory, CPU6502 &cpu);
