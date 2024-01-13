#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericINR(Memory &memory, I8080 &cpu, BYTE &targetRegister) {
    const BYTE targetCopy = targetRegister;
    targetRegister += 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(targetRegister, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlag(targetCopy, targetRegister);
}

inline void I8080_INR_A(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.A);
}

inline void I8080_INR_B(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.B);
}

inline void I8080_INR_C(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.C);
}

inline void I8080_INR_D(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.D);
}

inline void I8080_INR_E(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.E);
}

inline void I8080_INR_H(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.H);
}

inline void I8080_INR_L(Memory &memory, I8080 &cpu) {
    GenericINR(memory, cpu, cpu.L);
}

FORCE_INLINE void I8080_INR_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::SwapRegistersAsWord(cpu.H, cpu.L);
    BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    const BYTE memoryCopy = memoryValue;
    memoryValue += 1;
    cpu.WriteByte(memory, memoryValue, memoryAddress);
    cpu.Status.UpdateStatusByValue(memoryValue, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlag(memoryCopy, memoryValue);
}
