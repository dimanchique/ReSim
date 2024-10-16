#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Logical AND (generic)
 * @details A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A&M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform AND with register A.
 */
FORCE_INLINE void GenericAND(MOS6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Arithmetic Shift Left – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param affectingRegister Register value used as offset.
 */
FORCE_INLINE void MOS6502_AND_ABS(Memory &memory, MOS6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_AND_ABS(memory, cpu, cpu.X);
}

/**
 * @instruction Arithmetic Shift Left – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_AND_ABS(memory, cpu, cpu.Y);
}

/**
 * @instruction Arithmetic Shift Left – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericAND(cpu, value);
}

/**
 * @instruction Arithmetic Shift Left – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_AND_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericAND(cpu, value);
}
