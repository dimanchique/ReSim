#pragma once
#include "I8080/I8080.h"

/**
 * @brief Exchange
 * @details Exchange DE register value with HL register value.
 * @short DE <-> HL
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_XCHG(I8080 &cpu) {
    const WORD tmp = cpu.DE;
    cpu.DE = cpu.HL;
    cpu.HL = tmp;
    cpu.cycles++;
}
