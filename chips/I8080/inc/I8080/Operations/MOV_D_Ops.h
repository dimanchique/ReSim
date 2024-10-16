#pragma once
#include "MOV_Ops.h"

void I8080_MOV_D_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.A);
}

void I8080_MOV_D_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.B);
}

void I8080_MOV_D_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.C);
}

void I8080_MOV_D_D(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

void I8080_MOV_D_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.E);
}

void I8080_MOV_D_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.H);
}

void I8080_MOV_D_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.L);
}

void I8080_MOV_D_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.D);
}
