#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericORA(I8080 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}

FORCE_INLINE void I8080_ORA_A(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.A);
}

FORCE_INLINE void I8080_ORA_B(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.B);
}

FORCE_INLINE void I8080_ORA_C(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.C);
}

FORCE_INLINE void I8080_ORA_D(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.D);
}

FORCE_INLINE void I8080_ORA_E(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.E);
}

FORCE_INLINE void I8080_ORA_H(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.H);
}

FORCE_INLINE void I8080_ORA_L(Memory &memory, I8080 &cpu) {
    GenericORA(cpu, cpu.L);
}

FORCE_INLINE void I8080_ORA_M(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memory, memoryAddress);
    GenericORA(cpu, value);
}
