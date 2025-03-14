#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to A
 * @details This instruction is nop-like instruction
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_A(I8080 &cpu) {
    cpu.cycles++; //nop-like
}

/**
 * @brief MOV from B to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_B(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.B);
}

/**
 * @brief MOV from C to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_C(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.C);
}

/**
 * @brief MOV from D to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_D(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.D);
}

/**
 * @brief MOV from E to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_E(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.E);
}

/**
 * @brief MOV from H to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_H(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.H);
}

/**
 * @brief MOV from L to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_L(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.A, cpu.L);
}

/**
 * @brief MOV from Memory to A
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_A_M(I8080 &cpu) {
    PerformMemToRegMOV(cpu, cpu.A);
}
