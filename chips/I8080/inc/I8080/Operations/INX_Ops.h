#pragma once
#include "I8080/I8080.h"

/**
 * @brief Increment Register Pair Implementation
 * @details The 16-bit number held in the specified register pair is incremented by one.
 * @short Register = Register+1
 * @note Condition bits are not affected
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to increment.
 */
FORCE_INLINE void PerformINX(I8080 &cpu, WORD &targetRegister) {
    targetRegister++;
    cpu.cycles++;
}

/**
 * @brief Increment BC
 * @param cpu I8080 struct instance.
 */
void I8080_INX_B(I8080 &cpu) {
    PerformINX(cpu, cpu.BC);
}

/**
 * @brief Increment DE
 * @param cpu I8080 struct instance.
 */
void I8080_INX_D(I8080 &cpu) {
    PerformINX(cpu, cpu.DE);
}

/**
 * @brief Increment HL
 * @param cpu I8080 struct instance.
 */
void I8080_INX_H(I8080 &cpu) {
    PerformINX(cpu, cpu.HL);
}

/**
 * @brief Increment SP
 * @param cpu I8080 struct instance.
 */
void I8080_INX_SP(I8080 &cpu) {
    PerformINX(cpu, cpu.SP);
}
