#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Logical Inclusive OR (generic)
 * @details An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A|M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform OR with register A.
 */
FORCE_INLINE void GenericORA(MOS6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Logical Inclusive OR – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param affectingRegister Register value used as offset.
 */
FORCE_INLINE void MOS6502_ORA_ABS(Memory &memory, MOS6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ORA_ABS(memory, cpu, cpu.X);
}

/**
 * @instruction Logical Inclusive OR – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ORA_ABS(memory, cpu, cpu.Y);
}

/**
 * @instruction Logical Inclusive OR – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericORA(cpu, value);
}

/**
 * @instruction Logical Inclusive OR – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ORA_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericORA(cpu, value);
}
