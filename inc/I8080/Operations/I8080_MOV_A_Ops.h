#pragma once
#include "I8080_MOV_Ops.h"

inline void I8080_MOV_A_A(Memory &memory, I8080 &cpu) {
    // nop-like
}

inline void I8080_MOV_A_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.B);
}

inline void I8080_MOV_A_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.C);
}

inline void I8080_MOV_A_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.D);
}

inline void I8080_MOV_A_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.E);
}

inline void I8080_MOV_A_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.H);
}

inline void I8080_MOV_A_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.A, cpu.L);
}

inline void I8080_MOV_A_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.A);
}
