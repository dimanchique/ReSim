#pragma once
#include "MOV_Ops.h"

void I8080_MOV_B_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.A);
}

void I8080_MOV_B_B(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

void I8080_MOV_B_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.C);
}

void I8080_MOV_B_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.D);
}

void I8080_MOV_B_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.E);
}

void I8080_MOV_B_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.H);
}

void I8080_MOV_B_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.L);
}

void I8080_MOV_B_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.B);
}
