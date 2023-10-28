#pragma once
#include "CPU6502.h"

/**
 * @instruction Subtract with Carry (generic)
 * @description
 * This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit.
 * If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
 * @short A,Z,C,N = A-M-(1-C)
 * @param cpu CPU6502 struct instance
 * @param value Value to subtract
 */
inline void GenericSBC(CPU6502 &cpu, const BYTE value) {
    const bool AreSignBitsTheSame = !((cpu.A ^ value) & CPU6502_Status_N);
    const WORD Sub = cpu.A - value - (1 - cpu.Status.C);
    cpu.A = Sub;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sub > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ value) & CPU6502_Status_N));
}

/**
 * @instruction Subtract with Carry
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing Absolute,Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing (Indirect,X)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Subtract with Carry
 * @addressing (Indirect),Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_SBC_INDY(Memory &memory, CPU6502 &cpu);
