#pragma once
#include "MOV_Ops.h"

void I8080_MOV_H_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.A);
}

void I8080_MOV_H_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.B);
}

void I8080_MOV_H_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.C);
}

void I8080_MOV_H_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.D);
}

void I8080_MOV_H_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.E);
}

void I8080_MOV_H_H(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

 void I8080_MOV_H_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.L);
}

void I8080_MOV_H_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.H);
}
