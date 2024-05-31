#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericSubRegister(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD subResult = (WORD)cpu.A - targetRegister;
    cpu.Status.C = ((subResult & 0x0100) != 0);
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_P);
    cpu.Status.S = subResult > 0xFF;
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister);
}

inline void I8080_SUB_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    cpu.Status.C = 0;
    cpu.A = 0; // because A - A always 0
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator);
}

inline void I8080_SUB_B(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.B);
}

inline void I8080_SUB_C(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.C);
}

inline void I8080_SUB_D(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.D);
}

inline void I8080_SUB_E(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.E);
}

inline void I8080_SUB_H(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.H);
}

inline void I8080_SUB_L(Memory &memory, I8080 &cpu) {
    GenericSubRegister(memory, cpu, cpu.L);
}

inline void I8080_SUB_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    const BYTE subValue = cpu.ReadByte(memory, memoryAddress);
    GenericSubRegister(memory, cpu, subValue);
}

inline void I8080_SUI(Memory &memory, I8080 &cpu) {
    const BYTE subValue = cpu.FetchByte(memory);
    GenericSubRegister(memory, cpu, subValue);
}