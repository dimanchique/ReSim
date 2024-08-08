#pragma once
#include "MOV_Ops.h"

inline void I8080_MOV_C_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.A);
}

inline void I8080_MOV_C_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.B);
}

inline void I8080_MOV_C_C(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

inline void I8080_MOV_C_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.D);
}

inline void I8080_MOV_C_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.E);
}

inline void I8080_MOV_C_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.H);
}

inline void I8080_MOV_C_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.C, cpu.L);
}

inline void I8080_MOV_C_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.C);
}
