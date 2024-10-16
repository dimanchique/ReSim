#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericRotateLeft(I8080 &cpu, const bool isThroughCarry) {
    const bool carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= isThroughCarry ? cpu.Status.C : carry;
    cpu.Status.C = carry;
}

FORCE_INLINE void GenericRotateRight(I8080 &cpu, const bool isThroughCarry) {
    const bool carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= (isThroughCarry ? cpu.Status.C : carry) << 7;
    cpu.Status.C = carry;
}

void I8080_RLC(Memory &memory, I8080 &cpu) {
    GenericRotateLeft(cpu, false);
}

void I8080_RRC(Memory &memory, I8080 &cpu) {
    GenericRotateRight(cpu, false);
}

void I8080_RAL(Memory &memory, I8080 &cpu) {
    GenericRotateLeft(cpu, true);
}

void I8080_RAR(Memory &memory, I8080 &cpu) {
    GenericRotateRight(cpu, true);
}
