#pragma once
#include "I8080.h"

/**
 * @brief Decimal Adjust Accumulator
 * @details Description: The eight-bit hexadecimal number in the Accumulator is adjusted to form two four bit binary-coded
 * decimal digits by the following two step process:
 * 1) If the least significant four bits of the Accumulator represents a number greater than 9, or if the Auxiliary
 * Carry bit is equal to one, the Accumulator is incremented by six. Otherwise, no incrementing occurs.
 * 2) If the most significant four bits of the Accumulator now represent a number greater than 9, or if the normal
 * carry bit is equal to one, the most significant four bits of the Accumulator are incremented by six.
 * Otherwise, no incrementing occurs.
 * @param cpu I8080 struct instance.
 */
void I8080_DAA(I8080 &cpu) {
    BYTE slice = cpu.A & 0xF;
    if (slice > 9 || cpu.Status.AC)
    {
        cpu.A += 6;
        slice += 6;
        cpu.Status.AC = slice >> 4;
    }

    slice = (cpu.A >> 4) & 0xF;
    if (slice > 9 || cpu.Status.C)
    {
        slice += 6;
        cpu.Status.C = slice >> 4;
        slice &= 0xF;
        cpu.A &= 0xF;
        slice <<= 4;
        cpu.A |= slice;
    }
}
