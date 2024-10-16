#pragma once
#include "MOV_Ops.h"

void I8080_MOV_A_A(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

void I8080_MOV_A_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.B);
}

void I8080_MOV_A_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.C);
}

void I8080_MOV_A_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.D);
}

void I8080_MOV_A_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.E);
}

void I8080_MOV_A_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.H);
}

void I8080_MOV_A_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.L);
}

void I8080_MOV_A_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.A);
}
