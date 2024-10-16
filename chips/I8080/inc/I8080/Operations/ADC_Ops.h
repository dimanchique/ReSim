#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericAddRegisterWithCarry(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A + targetRegister + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister, cachedCarry);
}

void I8080_ADC_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = (cpu.A << 1) + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator, cachedCarry);
}

void I8080_ADC_B(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.B);
}

void I8080_ADC_C(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.C);
}

void I8080_ADC_D(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.D);
}

void I8080_ADC_E(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.E);
}

void I8080_ADC_H(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.H);
}

void I8080_ADC_L(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.L);
}

void I8080_ADC_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE addValue = cpu.ReadByte(memory, memoryAddress);
    GenericAddRegisterWithCarry(memory, cpu, addValue);
}

void I8080_ACI(Memory &memory, I8080 &cpu) {
    const BYTE addValue = cpu.FetchByte(memory);
    GenericAddRegisterWithCarry(memory, cpu, addValue);
}
