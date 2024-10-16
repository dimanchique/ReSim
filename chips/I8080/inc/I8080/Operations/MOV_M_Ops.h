#pragma once
#include "MOV_Ops.h"

void I8080_MOV_M_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.A);
}

void I8080_MOV_M_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.B);
}

void I8080_MOV_M_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.C);
}

void I8080_MOV_M_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.D);
}

void I8080_MOV_M_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.E);
}

void I8080_MOV_M_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.H);
}

void I8080_MOV_M_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.L);
}
