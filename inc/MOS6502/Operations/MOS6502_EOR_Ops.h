#pragma once

#include "MOS6502/MOS6502.h"

/**
 * @instruction Exclusive OR (generic)
 * @details An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
 * @short A,Z,N = A^M
 * @param cpu MOS6502 struct instance.
 * @param value Value to perform XOR with register A.
 */
FORCE_INLINE void GenericEOR(MOS6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Exclusive OR – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param affectingRegister Register value used as offset.
 */
FORCE_INLINE void MOS6502_EOR_ABS(Memory &memory, MOS6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_EOR_ABS(memory, cpu, cpu.X);
}

/**
 * @instruction Exclusive OR – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_EOR_ABS(memory, cpu, cpu.Y);
}

/**
 * @instruction Exclusive OR – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericEOR(cpu, value);
}

/**
 * @instruction Exclusive OR – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_EOR_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericEOR(cpu, value);
}
