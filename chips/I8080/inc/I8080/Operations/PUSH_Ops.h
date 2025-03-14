#pragma once
#include "I8080/I8080.h"

/**
 * @brief Push BC Data Onto Stack
 * @details The contents of the specified register pair are saved in two bytes of memory indicated by the stack pointer SP.
 * @short BC -> Stack
 * @param cpu I8080 struct instance.
 */
void I8080_PUSH_B(I8080 &cpu) {
    cpu.PushDataToStack(cpu.B, cpu.C);
}

/**
 * @brief Push DE Data Onto Stack
 * @details The contents of the specified register pair are saved in two bytes of memory indicated by the stack pointer SP.
 * @short DE -> Stack
 * @param cpu I8080 struct instance.
 */
void I8080_PUSH_D(I8080 &cpu) {
    cpu.PushDataToStack(cpu.D, cpu.E);
}

/**
 * @brief Push HL Data Onto Stack
 * @details The contents of the specified register pair are saved in two bytes of memory indicated by the stack pointer SP.
 * @short HL -> Stack
 * @param cpu I8080 struct instance.
 */
void I8080_PUSH_H(I8080 &cpu) {
    cpu.PushDataToStack(cpu.H, cpu.L);
}

/**
 * @brief Push Accumulator/Status Data Onto Stack
 * @details The contents of the specified register pair are saved in two bytes of memory indicated by the stack pointer SP.
 * @short Accumulator/Status -> Stack
 * @param cpu I8080 struct instance.
 */
void I8080_PUSH_PSW(I8080 &cpu) {
    cpu.PushDataToStack(cpu.A, cpu.Status.Value);
}
