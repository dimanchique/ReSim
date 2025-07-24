#pragma once
#include "MOV_Ops.h"

/**
 * @brief MOV from A to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_A(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.A);
}

/**
 * @brief MOV from B to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_B(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.B);
}

/**
 * @brief MOV from C to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_C(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.C);
}

/**
 * @brief MOV from D to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_D(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.D);
}

/**
 * @brief MOV from E to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_E(I8080 &cpu) {
    PerformRegToRegMOV(cpu, cpu.H, cpu.E);
}

/**
 * @brief MOV from H to H
 * @details This instruction is nop-like instruction
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_H(I8080 &cpu) {
    ++cpu.cycles; //nop-like
}

/**
 * @brief MOV from L to H
 * @param cpu I8080 struct instance.
 */
 void I8080_MOV_H_L(I8080 &cpu) {
     PerformRegToRegMOV(cpu, cpu.H, cpu.L);
}

/**
 * @brief MOV from Memory to H
 * @param cpu I8080 struct instance.
 */
void I8080_MOV_H_M(I8080 &cpu) {
    PerformMemToRegMOV(cpu, cpu.H);
}
