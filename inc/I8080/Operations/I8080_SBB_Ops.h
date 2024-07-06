#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericSBBRegister(Memory &memory, I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const BYTE twosComplement = ~(targetRegister + cpu.Status.C) + 1;
    const WORD subResult = (WORD)cpu.A + twosComplement;
    const bool carryOut = ((subResult & 0x0100) != 0);
    if (carryOut)
        cpu.Status.C = 0;
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_P);
    cpu.Status.S = initialAccumulator < targetRegister;
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, twosComplement);
}

inline void I8080_SBB_A(Memory &memory, I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD subResult = (WORD)cpu.A + (~cpu.A + 1 + cpu.Status.C);
    cpu.Status.C = ((subResult & 0x0100) != 0);
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator);
}

inline void I8080_SBB_B(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.B);
}

inline void I8080_SBB_C(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.C);
}

inline void I8080_SBB_D(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.D);
}

inline void I8080_SBB_E(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.E);
}

inline void I8080_SBB_H(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.H);
}

inline void I8080_SBB_L(Memory &memory, I8080 &cpu) {
    GenericSBBRegister(memory, cpu, cpu.L);
}

inline void I8080_SBB_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    const BYTE subValue = cpu.ReadByte(memory, memoryAddress);
    GenericSBBRegister(memory, cpu, subValue);
}

inline void I8080_SBI(Memory &memory, I8080 &cpu) {
    const BYTE subValue = cpu.FetchByte(memory);
    GenericSBBRegister(memory, cpu, subValue);
}