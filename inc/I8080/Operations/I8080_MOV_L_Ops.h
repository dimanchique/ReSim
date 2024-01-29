#pragma once
#include "I8080_MOV_Ops.h"

inline void I8080_MOV_L_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.A);
}

inline void I8080_MOV_L_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.B);
}

inline void I8080_MOV_L_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.C);
}

inline void I8080_MOV_L_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.D);
}

inline void I8080_MOV_L_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.E);
}

inline void I8080_MOV_L_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.L, cpu.H);
}

inline void I8080_MOV_L_L(Memory &memory, I8080 &cpu) {
    // nop-like
}

inline void I8080_MOV_L_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.L);
}
