#pragma once
#include "I8080_MOV_Ops.h"

inline void I8080_MOV_E_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.A);
}

inline void I8080_MOV_E_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.B);
}

inline void I8080_MOV_E_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.C);
}

inline void I8080_MOV_E_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.D);
}

inline void I8080_MOV_E_E(Memory &memory, I8080 &cpu) {
    cpu.cycles++; //nop-like
}

inline void I8080_MOV_E_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.H);
}

inline void I8080_MOV_E_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToReg(cpu, cpu.E, cpu.L);
}

inline void I8080_MOV_E_M(Memory &memory, I8080 &cpu) {
    GenericMOV_MemToReg(memory, cpu, cpu.E);
}
