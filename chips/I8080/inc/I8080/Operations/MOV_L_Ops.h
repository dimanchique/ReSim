#pragma once
#include "MOV_Ops.h"

void I8080_MOV_L_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.A);
}

void I8080_MOV_L_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.B);
}

void I8080_MOV_L_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.C);
}

void I8080_MOV_L_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.D);
}

void I8080_MOV_L_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.E);
}

void I8080_MOV_L_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.H);
}

void I8080_MOV_L_L(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

void I8080_MOV_L_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.L);
}
