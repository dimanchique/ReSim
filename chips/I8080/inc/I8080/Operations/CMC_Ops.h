#pragma once
#include "I8080/I8080.h"

/**
 * @brief Complement Carry
 * @details Complement Carry flag value
 * @short C = !C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_CMC(I8080 &cpu) {
    cpu.Status.C = !cpu.Status.C;
}
