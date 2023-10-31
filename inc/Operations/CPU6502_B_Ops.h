#pragma once
#include "CPU6502.h"

/**
 * @instruction Branch (generic)
 * @details If the targetFlag is equal to expectedValue then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetFlag Status flag to check.
 * @param expectedValue Expected value of status flag.
 */
inline void GenericB(Memory &memory, CPU6502 &cpu, const BYTE targetFlag, const bool expectedValue) {
    const SBYTE Offset = cpu.FetchByte(memory);
    if (targetFlag == expectedValue) {
        cpu.cycles++;
        if (IsPageCrossed(cpu.PC, cpu.PC + Offset))
            cpu.cycles++;
        cpu.PC += Offset;
    }
}

/**
 * @instruction Branch if Carry Clear – Relative
 * @details If the carry flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BCC_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Carry Set – Relative
 * @details If the carry flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BCS_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Equal – Relative
 * @details If the zero flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BEQ_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Not Equal – Relative
 * @details If the zero flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BNE_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Minus – Relative
 * @details If the negative flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BMI_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Positive – Relative
 * @details If the negative flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BPL_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Overflow Clear – Relative
 * @details If the overflow flag is clear then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BVC_REL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Branch if Overflow Set – Relative
 * @details If the overflow flag is set then add the relative displacement to the program counter
 * to cause a branch to a new location.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BVS_REL(Memory &memory, CPU6502 &cpu);
