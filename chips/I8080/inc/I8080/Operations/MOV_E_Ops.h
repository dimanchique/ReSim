#pragma once
#include "MOV_Ops.h"

void I8080_MOV_E_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.A);
}

void I8080_MOV_E_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.B);
}

void I8080_MOV_E_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.C);
}

void I8080_MOV_E_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.D);
}

void I8080_MOV_E_E(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

void I8080_MOV_E_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.H);
}

void I8080_MOV_E_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.L);
}

void I8080_MOV_E_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.E);
}
