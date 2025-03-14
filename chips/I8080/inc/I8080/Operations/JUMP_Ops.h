#pragma once
#include "I8080/I8080.h"

/**
 * @brief JUMP Implementation
 * @details The JUMP instruction sets the program counter to the target memory address (immediate value)
 * @note This function surveys conditional RETURN instructions: C(N)C, C(N)Z, CM, CP, CPE, CPO.
 * If function called from conditional RETURN, conditionFlag is required.
 * @short PC = Memory
 * @param cpu I8080 struct instance.
 * @param conditionFlag Condition flag value if instruction is conditional (default true).
 */
FORCE_INLINE void PerformJump(I8080 &cpu, const bool conditionFlag = true) {
    const WORD newPC = cpu.FetchWord();
    if (conditionFlag)
        cpu.PC = newPC;
}

/**
 * @brief Absolute Jump
 * @details Absolute (unconditional) JUMP instruction. Sets the program counter to the target memory address (immediate value)
 * @param cpu I8080 struct instance.
 */
void I8080_JMP(I8080 &cpu) {
    PerformJump(cpu);
}

/**
 * @brief Jump if Carry
 * @details Conditional JUMP instruction. Performs jump if carry flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_JC(I8080 &cpu) {
    PerformJump(cpu, cpu.Status.C);
}

/**
 * @brief Jump if Not Carry
 * @details Conditional JUMP instruction. Performs jump if carry flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_JNC(I8080 &cpu) {
    PerformJump(cpu, !cpu.Status.C);
}

/**
 * @brief Jump if Minus
 * @details Conditional JUMP instruction. Performs jump if sign flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_JM(I8080 &cpu) {
    PerformJump(cpu, cpu.Status.S);
}

/**
 * @brief Jump if Positive
 * @details Conditional JUMP instruction. Performs jump if sign flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_JP(I8080 &cpu) {
    PerformJump(cpu, !cpu.Status.S);
}

/**
 * @brief Jump if Zero
 * @details Conditional JUMP instruction. Performs jump if zero flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_JZ(I8080 &cpu) {
    PerformJump(cpu, cpu.Status.Z);
}

/**
 * @brief Jump if Not Zero
 * @details Conditional JUMP instruction. Performs jump if zero flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_JNZ(I8080 &cpu) {
    PerformJump(cpu, !cpu.Status.Z);
}

/**
 * @brief Jump if Parity Even
 * @details Conditional JUMP instruction. Performs jump if parity flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_JPE(I8080 &cpu) {
    PerformJump(cpu, cpu.Status.P);
}

/**
 * @brief Jump if Parity Odd
 * @details Conditional JUMP instruction. Performs jump if parity flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_JPO(I8080 &cpu) {
    PerformJump(cpu, !cpu.Status.P);
}
