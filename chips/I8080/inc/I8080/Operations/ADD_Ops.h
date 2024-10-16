#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericAddRegister(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A + targetRegister;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister);
}

void I8080_ADD_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A << 1;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator);
}

void I8080_ADD_B(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.B);
}

void I8080_ADD_C(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.C);
}

void I8080_ADD_D(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.D);
}

void I8080_ADD_E(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.E);
}

void I8080_ADD_H(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.H);
}

void I8080_ADD_L(Memory &memory, I8080 &cpu) {
    GenericAddRegister(memory, cpu, cpu.L);
}

void I8080_ADD_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE addValue = cpu.ReadByte(memory, memoryAddress);
    GenericAddRegister(memory, cpu, addValue);
}

void I8080_ADI(Memory &memory, I8080 &cpu) {
    const BYTE addValue = cpu.FetchByte(memory);
    GenericAddRegister(memory, cpu, addValue);
}
