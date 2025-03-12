#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_A(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.A);
}

/**
 * @brief MOV from B to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_B(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.B);
}

/**
 * @brief MOV from C to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_C(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.C);
}

/**
 * @brief MOV from D to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_D(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.D);
}

/**
 * @brief MOV from E to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_E(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.E);
}

/**
 * @brief MOV from H to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_H(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.H);
}

/**
 * @brief MOV from L to Memory
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_M_L(I8080 &cpu) {
    PerformRegToMemMOV(cpu, cpu.L);
}
