#pragma once
#include "CPU6502.h"

/**
 * @instruction Logical AND (generic)
 * @details A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A&M
 * @param cpu CPU6502 struct instance.
 * @param value Value to perform AND with register A.
 */
inline void GenericAND(CPU6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

/**
 * @instruction Arithmetic Shift Left – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Arithmetic Shift Left – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_AND_INDY(Memory &memory, CPU6502 &cpu);
