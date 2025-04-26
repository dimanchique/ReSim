#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_A(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.A);
}

/**
 * @brief MOV from B to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_B(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.B);
}

/**
 * @brief MOV from C to C
 * @details This instruction is nop-like instruction
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_C(I8080 &cpu) {
    ++cpu.cycles; //nop-like
}

/**
 * @brief MOV from D to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_D(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.D);
}

/**
 * @brief MOV from E to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_E(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.E);
}

/**
 * @brief MOV from H to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_H(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.H);
}

/**
 * @brief MOV from L to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_L(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.C, cpu.L);
}

/**
 * @brief MOV from Memory to C
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_C_M(I8080 &cpu) {
    PerformMemToRegMOV(cpu, cpu.C);
}
