#pragma once
#include "I8080.h"

/**
 * @brief Complement Accumulator
 * @details Complement Accumulator register value bit by bit
 * @short A = ~A
 * @param cpu I8080 struct instance.
 */
void I8080_CMA(I8080 &cpu) {
    cpu.A = ~cpu.A;
}

/**
 * @brief Complement Carry
 * @details Complement Carry flag value
 * @short C = !C
 * @param cpu I8080 struct instance.
 */
void I8080_CMC(I8080 &cpu) {
    cpu.Status.C = !cpu.Status.C;
}
