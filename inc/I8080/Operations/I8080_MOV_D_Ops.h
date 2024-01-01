#pragma once

#include "I8080_MOV_Ops.h"

inline void I8080_MOV_D_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.A);
}

inline void I8080_MOV_D_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.B);
}

inline void I8080_MOV_D_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.C);
}

inline void I8080_MOV_D_D(Memory &memory, I8080 &cpu) {
    // nop-like
}

inline void I8080_MOV_D_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.E);
}

inline void I8080_MOV_D_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.H);
}

inline void I8080_MOV_D_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.D, cpu.L);
}

inline void I8080_MOV_D_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.D);
}
