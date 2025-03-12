#pragma once
#include "I8080/I8080.h"

/**
 * @brief Logical AND Immediate value
 * @details A logical AND Immediate is performed, bit by bit, on the Accumulator contents using immediate value.
 * @short A,S,P,Z = A&MemImm
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ANI(I8080 &cpu) {
    const BYTE memoryValue = cpu.FetchByte();
    cpu.A &= memoryValue;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}
