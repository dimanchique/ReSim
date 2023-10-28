#pragma once
#include "CPU6502.h"

/**
 * @instruction Logical Inclusive OR (generic)
 * @description
 * An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A|M
 * @param cpu CPU6502 struct instance
 * @param value Value to perform OR with register A
 */
inline void GenericORA(CPU6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

/**
 * @instruction Logical Inclusive OR
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing Absolute,Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing (Indirect,X)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Logical Inclusive OR
 * @addressing (Indirect),Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_ORA_INDY(Memory &memory, CPU6502 &cpu);
