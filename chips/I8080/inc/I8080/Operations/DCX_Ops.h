#pragma once
#include "I8080/I8080.h"

/**
 * @brief Decrement Register Pair Implementation
 * @details The 16-bit number held in the specified register pair is decremented by one.
 * @short Register = Register-1
 * @note Condition bits are not affected
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to decrement.
 */
FORCE_INLINE void PerformDCX(I8080 &cpu, WORD &targetRegister) {
    targetRegister = (WORD)(targetRegister + 0xFFFF); // +(-1) is better than -1
    cpu.cycles++;
}

/**
 * @brief Decrement BC
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCX_B(I8080 &cpu) {
    PerformDCX(cpu, cpu.BC);
}

/**
 * @brief Decrement DE
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCX_D(I8080 &cpu) {
    PerformDCX(cpu, cpu.DE);
}

/**
 * @brief Decrement HL
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCX_H(I8080 &cpu) {
    PerformDCX(cpu, cpu.HL);
}

/**
 * @brief Decrement SP
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_DCX_SP(I8080 &cpu) {
    PerformDCX(cpu, cpu.SP);
}
