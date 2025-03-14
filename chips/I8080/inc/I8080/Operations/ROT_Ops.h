#pragma once
#include "I8080/I8080.h"

/**
 * @brief Rotate Left Implementation
 * @details The content of the Accumulator is rotating left
 * @note Accumulator can be rotated circularly or through Carry.
 * Circular rotation means bit 7 is moved to bit 0 after operation is performed.
 * Rotation through carry means Carry flag is moved to bit 0 after operation is performed.
 * In both modes bit 7 of Accumulator before rotation is a new Carry flag.
 * @short A = A<<1, C = prevA&0b1000000
 * @param cpu I8080 struct instance.
 * @param isThroughCarry Through Carry rotation mode.
 */
FORCE_INLINE void PerformRotateLeft(I8080 &cpu, const bool isThroughCarry) {
    const bool carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= isThroughCarry ? cpu.Status.C : carry;
    cpu.Status.C = carry;
}

/**
 * @brief Rotate Right Implementation
 * @details The content of the Accumulator is rotating right
 * @note Accumulator can be rotated circularly or through Carry.
 * Circular rotation means bit 0 is moved to bit 7 after operation is performed.
 * Rotation through carry means Carry flag is moved to bit 7 after operation is performed.
 * In both modes bit 0 of Accumulator before rotation is a new Carry flag.
 * @short A = A>>1, C = prevA&0b0000001
 * @param cpu I8080 struct instance.
 * @param isThroughCarry Through Carry rotation mode.
 */
FORCE_INLINE void PerformRotateRight(I8080 &cpu, const bool isThroughCarry) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= (isThroughCarry ? cpu.Status.C : carry) << 7;
    cpu.Status.C = carry;
}

/**
 * @brief Circular Rotate Accumulator Left
 * @short A = A<<1, C = prevA&0b1000000
 * @param cpu I8080 struct instance.
 */
void I8080_RLC(I8080 &cpu) {
    PerformRotateLeft(cpu, false);
}

/**
 * @brief Circular Rotate Accumulator Right
 * @short A = A>>1, C = prevA&0b0000001
 * @param cpu I8080 struct instance.
 */
void I8080_RRC(I8080 &cpu) {
    PerformRotateRight(cpu, false);
}

/**
 * @brief Rotate Accumulator Left Through Carry
 * @short A = A<<1, C = prevA&0b1000000
 * @param cpu I8080 struct instance.
 */
void I8080_RAL(I8080 &cpu) {
    PerformRotateLeft(cpu, true);
}

/**
 * @brief Rotate Accumulator Right Through Carry
 * @short A = A>>1, C = prevA&0b0000001
 * @param cpu I8080 struct instance.
 */
void I8080_RAR(I8080 &cpu) {
    PerformRotateRight(cpu, true);
}
