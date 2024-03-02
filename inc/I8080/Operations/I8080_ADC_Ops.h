#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericAddRegisterWithCarry(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A + targetRegister + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = (addResult & 0xFF00) > 0;
    cpu.A = addResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, targetRegister, cachedCarry);
}

inline void I8080_ADC_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = (cpu.A << 1) + cpu.Status.C;
    const BYTE cachedCarry = cpu.Status.C;
    cpu.Status.C = (addResult & 0xFF00) > 0;
    cpu.A = addResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator, cachedCarry);
}

inline void I8080_ADC_B(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.B);
}

inline void I8080_ADC_C(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.C);
}

inline void I8080_ADC_D(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.D);
}

inline void I8080_ADC_E(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.E);
}

inline void I8080_ADC_H(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.H);
}

inline void I8080_ADC_L(Memory &memory, I8080 &cpu) {
    GenericAddRegisterWithCarry(memory, cpu, cpu.L);
}

inline void I8080_ADC_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    const BYTE addValue = cpu.ReadByte(memory, memoryAddress);
    GenericAddRegisterWithCarry(memory, cpu, addValue);
}

inline void I8080_ACI(Memory &memory, I8080 &cpu) {
    const BYTE addValue = cpu.FetchByte(memory);
    GenericAddRegisterWithCarry(memory, cpu, addValue);
}
