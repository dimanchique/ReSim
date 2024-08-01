#pragma once
#include "I8080_MOV_Ops.h"

inline void I8080_MOV_M_A(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.A);
}

inline void I8080_MOV_M_B(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.B);
}

inline void I8080_MOV_M_C(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.C);
}

inline void I8080_MOV_M_D(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.D);
}

inline void I8080_MOV_M_E(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.E);
}

inline void I8080_MOV_M_H(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.H);
}

inline void I8080_MOV_M_L(Memory &memory, I8080 &cpu) {
    GenericMOV_RegToMem(memory, cpu, cpu.L);
}
