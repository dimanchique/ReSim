#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericXRA(I8080 &cpu, const BYTE value) {
    const BYTE targetCopy = cpu.A;
    cpu.A ^= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlag(targetCopy, cpu.A);
}

FORCE_INLINE void I8080_XRA_A(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.A);
}

FORCE_INLINE void I8080_XRA_B(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.B);
}

FORCE_INLINE void I8080_XRA_C(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.C);
}

FORCE_INLINE void I8080_XRA_D(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.D);
}

FORCE_INLINE void I8080_XRA_E(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.E);
}

FORCE_INLINE void I8080_XRA_H(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.H);
}

FORCE_INLINE void I8080_XRA_L(Memory &memory, I8080 &cpu) {
    GenericXRA(cpu, cpu.L);
}

FORCE_INLINE void I8080_XRA_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::SwapRegistersAsWord(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memory, memoryAddress);
    GenericXRA(cpu, value);
}
