#pragma once

#include "I8080_MOV_Ops.h"

inline void I8080_MOV_H_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.A);
}

inline void I8080_MOV_H_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.B);
}

inline void I8080_MOV_H_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.C);
}

inline void I8080_MOV_H_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.D);
}

inline void I8080_MOV_H_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.E);
}

inline void I8080_MOV_H_H(Memory &memory, I8080 &cpu) {
    // nop-like
}

inline void I8080_MOV_H_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.H, cpu.L);
}

inline void I8080_MOV_H_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.H);
}
