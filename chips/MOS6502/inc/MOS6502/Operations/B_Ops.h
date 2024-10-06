#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Branch (generic)
 * @details If the targetFlag is equal to expectedValue then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetFlag Status flag to check.
 * @param expectedValue Expected value of status flag.
 */
FORCE_INLINE void GenericB(Memory &memory, MOS6502 &cpu, const BYTE targetFlag, const bool expectedValue) {
    const SBYTE offset = (SBYTE)cpu.FetchByte(memory);
    if (targetFlag == expectedValue) {
        cpu.cycles++;
        if (IsPageCrossed(cpu.PC, cpu.PC + offset))
            cpu.cycles++;
        cpu.PC += offset;
    }
}

/**
 * @instruction Branch if Carry Clear – Relative
 * @details If the carry flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BCC_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.C, false);
}

/**
 * @instruction Branch if Carry Set – Relative
 * @details If the carry flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BCS_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.C, true);
}

/**
 * @instruction Branch if Equal – Relative
 * @details If the zero flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BEQ_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.Z, true);
}

/**
 * @instruction Branch if Not Equal – Relative
 * @details If the zero flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BNE_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.Z, false);
}

/**
 * @instruction Branch if Minus – Relative
 * @details If the negative flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BMI_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.N, true);
}

/**
 * @instruction Branch if Positive – Relative
 * @details If the negative flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BPL_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.N, false);
}

/**
 * @instruction Branch if Overflow Clear – Relative
 * @details If the overflow flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BVC_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.V, false);
}

/**
 * @instruction Branch if Overflow Set – Relative
 * @details If the overflow flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BVS_REL(Memory &memory, MOS6502 &cpu) {
    GenericB(memory, cpu, cpu.Status.V, true);
}
