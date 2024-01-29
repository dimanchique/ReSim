#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Decrement Memory (generic)
 * @details Subtracts one from the value held at a specified memory location
 * setting the zero and negative flags as appropriate.
 * @short M,Z,N = M-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param memoryValue Memory value to decrement.
 * @param address Address to write back modified value .
 */
FORCE_INLINE void GenericDEC(Memory &memory, MOS6502 &cpu, const WORD address) {
    BYTE memoryValue = memory[address];
    cpu.cycles++;
    memoryValue--;
    cpu.cycles++;
    cpu.WriteByte(memory, memoryValue, address);
    cpu.Status.UpdateStatusByValue(memoryValue, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Decrement Memory – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEC_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericDEC(memory, cpu, address);
}

/**
 * @instruction Decrement Memory – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEC_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericDEC(memory, cpu, address);
}

/**
 * @instruction Decrement Memory – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEC_ABS(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericDEC(memory, cpu, address);
}

/**
 * @instruction Decrement Memory – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEC_ABSX(Memory &memory, MOS6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericDEC(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}

/**
 * @instruction Decrement X Register – Implied
 * @short X,Z,N = X-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEX_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.X--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Decrement Y Register – Implied
 * @short Y,Z,N = Y-1
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_DEY_IMPL(Memory &memory, MOS6502 &cpu) {
    cpu.Y--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, MOS6502_Status_Z | MOS6502_Status_N);
}
