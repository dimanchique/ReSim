#pragma once
#include "I8080/I8080.h"

/**
 * @brief CALL Implementation
 * @details The CALL instruction pushes program counter register (PC) on to the stack
 * and sets the program counter to the target memory address (immediate value).
 * @note This function surveys conditional CALL instructions: C(N)C, C(N)Z, CM, CP, CPE, CPO.
 * If function called from conditional CALL, conditionFlag is required.
 * An extra cycles count increment is performed if the CALL instruction is conditional. It's a conditionFlag check 'cost'.
 * @short PC = Memory
 * @param cpu I8080 struct instance.
 * @param isConditional Whether instruction is conditional or not (default false).
 * @param conditionFlag Condition flag value if instruction is conditional (default false).
 */
FORCE_INLINE void PerformCall(I8080 &cpu, const bool isConditional = false, const bool conditionFlag = false) {
    const WORD newPC = cpu.FetchWord();
    // isConditional is normally false (by default), and we need to do CALL, but if it's not - check conditionFlag first
    if (!isConditional || conditionFlag) {
        cpu.PushProgramCounterToStack();
        cpu.PC = newPC;
    }
    if (isConditional)
        cpu.cycles++;
}

/**
 * @brief Absolute Call
 * @details Absolute (unconditional) CALL instruction. Pushes program counter register (PC) on to the stack
 * and sets the program counter to the target memory address (immediate value).
 * @param cpu I8080 struct instance.
 */
void I8080_CALL(I8080 &cpu) {
    PerformCall(cpu);
}

/**
 * @brief Call if Carry
 * @details Conditional CALL instruction. Performs call if carry flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_CC(I8080 &cpu) {
    PerformCall(cpu, true, cpu.Status.C);
}

/**
 * @brief Call if Not Carry
 * @details Conditional CALL instruction. Performs call if carry flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_CNC(I8080 &cpu) {
    PerformCall(cpu, true, !cpu.Status.C);
}

/**
 * @brief Call if Minus
 * @details Conditional CALL instruction. Performs call if sign flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_CM(I8080 &cpu) {
    PerformCall(cpu, true, cpu.Status.S);
}

/**
 * @brief Call if Positive
 * @details Conditional CALL instruction. Performs call if sign flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_CP(I8080 &cpu) {
    PerformCall(cpu, true, !cpu.Status.S);
}

/**
 * @brief Call if Zero
 * @details Conditional CALL instruction. Performs call if zero flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_CZ(I8080 &cpu) {
    PerformCall(cpu, true, cpu.Status.Z);
}

/**
 * @brief Call if Not Zero
 * @details Conditional CALL instruction. Performs call if zero flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_CNZ(I8080 &cpu) {
    PerformCall(cpu, true, !cpu.Status.Z);
}

/**
 * @brief Call if Parity Even
 * @details Conditional CALL instruction. Performs call if parity flag is set
 * @param cpu I8080 struct instance.
 */
void I8080_CPE(I8080 &cpu) {
    PerformCall(cpu, true, cpu.Status.P);
}

/**
 * @brief Call if Parity Odd
 * @details Conditional CALL instruction. Performs call if parity flag is unset
 * @param cpu I8080 struct instance.
 */
void I8080_CPO(I8080 &cpu) {
    PerformCall(cpu, true, !cpu.Status.P);
}
