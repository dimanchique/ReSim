#pragma once
#include "I8080/I8080.h"

/**
 * @brief Pop BC Data Off Stack
 * @details The contents of the specified register pair are restored from two bytes of memory indicated by the stack pointer SP.
 * @short BC <- Stack
 * @param cpu I8080 struct instance.
 */
void I8080_POP_B(I8080 &cpu) {
    cpu.PopDataFromStack(&cpu.B, &cpu.C);
}

/**
 * @brief Pop DE Data Off Stack
 * @details The contents of the specified register pair are restored from two bytes of memory indicated by the stack pointer SP.
 * @short DE <- Stack
 * @param cpu I8080 struct instance.
 */
void I8080_POP_D(I8080 &cpu) {
    cpu.PopDataFromStack(&cpu.D, &cpu.E);
}

/**
 * @brief Pop HL Data Off Stack
 * @details The contents of the specified register pair are restored from two bytes of memory indicated by the stack pointer SP.
 * @short HL <- Stack
 * @param cpu I8080 struct instance.
 */
void I8080_POP_H(I8080 &cpu) {
    cpu.PopDataFromStack(&cpu.H, &cpu.L);
}

/**
 * @brief Pop Accumulator/Status Data Off Stack
 * @details The contents of the specified register pair are restored from two bytes of memory indicated by the stack pointer SP.
 * @short Accumulator/Status <- Stack
 * @param cpu I8080 struct instance.
 */
void I8080_POP_PSW(I8080 &cpu) {
    cpu.PopDataFromStack(&cpu.A, (BYTE *) &cpu.Status);
}
