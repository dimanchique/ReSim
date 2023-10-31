#pragma once
#include "CPU6502.h"

/**
 * @instruction Add with Carry (generic)
 * @details This instruction adds the contents of a memory location to the accumulator together with the carry bit.
 * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * @short A,Z,C,N = A+M+C
 * @param cpu CPU6502 struct instance.
 * @param value Value to add.
 */
inline void GenericADC(CPU6502 &cpu, const BYTE value) {
    const bool AreSignBitsTheSame = !((cpu.A ^ value) & CPU6502_Status_N);
    const WORD Sum = cpu.A + value + cpu.Status.C;
    cpu.A = Sum;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sum > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ value) & CPU6502_Status_N));
}

/**
 * @instruction Add with Carry – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Add with Carry – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_ADC_INDY(Memory &memory, CPU6502 &cpu);
