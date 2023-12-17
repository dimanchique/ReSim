#pragma once

#include "MOS6502.h"

/**
 * @instruction Subtract with Carry (generic)
 * @details This instruction subtracts the contents of a memory location to the accumulator
 * together with the not of the carry bit.
 * If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
 * @short A,Z,C,N = A-M-(1-C)
 * @param cpu MOS6502 struct instance.
 * @param value Value to subtract.
 */
FORCE_INLINE void GenericSBC(MOS6502 &cpu, const BYTE value) {
    const bool AreSignBitsTheSame = !((cpu.A ^ value) & MOS6502_Status_N);
    const WORD Sub = cpu.A - value - (1 - cpu.Status.C);
    cpu.A = Sub;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.SetStatusFlagValue(MOS6502_Status_C, Sub > 0xFF);
    cpu.Status.SetStatusFlagValue(MOS6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ value) & MOS6502_Status_N));
}

/**
 * @instruction Subtract with Carry – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – Zero Page
 * @param memory Memory struct instance
 * @param cpu MOS6502 struct instance
 */
inline void MOS6502_SBC_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_ABSX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory, cpu.X);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_ABSY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory, cpu.Y);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericSBC(cpu, value);
}

/**
 * @instruction Subtract with Carry – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_SBC_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericSBC(cpu, value);
}
