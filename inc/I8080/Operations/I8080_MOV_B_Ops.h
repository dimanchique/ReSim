#pragma once
#include "I8080_MOV_Ops.h"

inline void I8080_MOV_B_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.A);
}

inline void I8080_MOV_B_B(Memory &memory, I8080 &cpu) {
    // nop-like
}

inline void I8080_MOV_B_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.C);
}

inline void I8080_MOV_B_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.D);
}

inline void I8080_MOV_B_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.E);
}

inline void I8080_MOV_B_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.H);
}

inline void I8080_MOV_B_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.B, cpu.L);
}

inline void I8080_MOV_B_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.B);
}
