#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericMVI_MoveToReg(Memory& memory, I8080 &cpu, BYTE& targetRegister) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    targetRegister = immediateValue;
}

FORCE_INLINE void I8080_MVI_M(Memory& memory, I8080 &cpu) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    const WORD memoryAddress = I8080::SwapRegistersAsWord(cpu.H, cpu.L);
    cpu.WriteByte(memory, immediateValue, memoryAddress);
}

inline void I8080_MVI_A(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.A);
}

inline void I8080_MVI_B(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.B);
}

inline void I8080_MVI_C(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.C);
}

inline void I8080_MVI_D(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.D);
}

inline void I8080_MVI_E(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.E);
}

inline void I8080_MVI_H(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.H);
}

inline void I8080_MVI_L(Memory &memory, I8080 &cpu) {
    GenericMVI_MoveToReg(memory, cpu, cpu.L);
}
