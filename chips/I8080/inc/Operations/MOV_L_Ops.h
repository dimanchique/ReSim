#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_A(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.A);
}

/**
 * @brief MOV from B to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_B(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.B);
}

/**
 * @brief MOV from C to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_C(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.C);
}

/**
 * @brief MOV from D to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_D(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.D);
}

/**
 * @brief MOV from E to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_E(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.E);
}

/**
 * @brief MOV from H to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_H(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.L, cpu.H);
}

/**
 * @brief MOV from L to L
 * @details This instruction is nop-like instruction
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_L(I8080 &cpu) {
    ++cpu.cycles; //nop-like
}

/**
 * @brief MOV from Memory to L
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_L_M(I8080 &cpu) {
    PerformMemToRegMOV(cpu, cpu.L);
}
