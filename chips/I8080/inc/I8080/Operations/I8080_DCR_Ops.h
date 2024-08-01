#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericDCR(Memory &memory, I8080 &cpu, BYTE &targetRegister) {
    const BYTE targetCopy = targetRegister;
    targetRegister = (BYTE)(targetRegister + 0xFF);
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(targetRegister, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(targetCopy, 0xFF);
}

inline void I8080_DCR_A(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.A);
}

inline void I8080_DCR_B(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.B);
}

inline void I8080_DCR_C(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.C);
}

inline void I8080_DCR_D(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.D);
}

inline void I8080_DCR_E(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.E);
}

inline void I8080_DCR_H(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.H);
}

inline void I8080_DCR_L(Memory &memory, I8080 &cpu) {
    GenericDCR(memory, cpu, cpu.L);
}

FORCE_INLINE void I8080_DCR_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    const BYTE memoryCopy = memoryValue;
    memoryValue -= 1;
    cpu.WriteByte(memory, memoryValue, memoryAddress);
    cpu.Status.UpdateStatusByValue(memoryValue, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(memoryCopy, 0xFF);
}
