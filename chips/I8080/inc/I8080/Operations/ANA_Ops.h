#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericANA(I8080 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}

void I8080_ANA_A(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.A);
}

void I8080_ANA_B(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.B);
}

void I8080_ANA_C(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.C);
}

void I8080_ANA_D(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.D);
}

void I8080_ANA_E(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.E);
}

void I8080_ANA_H(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.H);
}

void I8080_ANA_L(Memory &memory, I8080 &cpu) {
    GenericANA(cpu, cpu.L);
}

void I8080_ANA_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memory, memoryAddress);
    GenericANA(cpu, value);
}
