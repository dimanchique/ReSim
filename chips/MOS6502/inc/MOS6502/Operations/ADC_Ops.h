#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Add with Carry (generic)
 * @details This instruction adds the contents of a memory location to the accumulator together with the carry bit.
 * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * @short A,Z,C,N = A+M+C
 * @param cpu MOS6502 struct instance.
 * @param value Value to add.
 */
FORCE_INLINE void GenericADC(MOS6502 &cpu, const BYTE value) {
    const bool AreSignBitsTheSame = !((cpu.A ^ value) & MOS6502_Status_N);
    const WORD Sum = cpu.A + value + cpu.Status.C;
    cpu.A = Sum;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.SetStatusFlagValue(MOS6502_Status_C, Sum > 0xFF);
    cpu.Status.SetStatusFlagValue(MOS6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ value) & MOS6502_Status_N));
}

/**
 * @instruction Add with Carry – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_IM(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_ZP(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_ZPX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_ABS(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param affectingRegister Register value used as offset.
 */
FORCE_INLINE void MOS6502_ADC_ABS(Memory &memory, MOS6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_ABSX(Memory &memory, MOS6502 &cpu) {
    MOS6502_ADC_ABS(memory, cpu, cpu.X);
}

/**
 * @instruction Add with Carry – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_ABSY(Memory &memory, MOS6502 &cpu) {
    MOS6502_ADC_ABS(memory, cpu, cpu.Y);
}

/**
 * @instruction Add with Carry – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_INDX(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericADC(cpu, value);
}

/**
 * @instruction Add with Carry – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
inline void MOS6502_ADC_INDY(Memory &memory, MOS6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericADC(cpu, value);
}
