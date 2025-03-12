#pragma once
#include "I8080/I8080.h"

/**
 * @brief Complement Accumulator
 * @details Complement Accumulator register value bit by bit
 * @short A = ~A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMA(I8080 &cpu) {
    cpu.A = ~cpu.A;
}
