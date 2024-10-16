#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericMVI(Memory &memory, I8080 &cpu, BYTE &targetRegister) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    targetRegister = immediateValue;
}

void I8080_MVI_A(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.A);
}

void I8080_MVI_B(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.B);
}

void I8080_MVI_C(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.C);
}

void I8080_MVI_D(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.D);
}

void I8080_MVI_E(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.E);
}

void I8080_MVI_H(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.H);
}

void I8080_MVI_L(Memory &memory, I8080 &cpu) {
    GenericMVI(memory, cpu, cpu.L);
}

void I8080_MVI_M(Memory &memory, I8080 &cpu) {
    const BYTE immediateValue = cpu.FetchByte(memory);
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.WriteByte(memory, immediateValue, memoryAddress);
}
