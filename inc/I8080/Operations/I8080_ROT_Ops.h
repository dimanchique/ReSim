#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericRotateLeft(I8080 &cpu, bool isThroughCarry){
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= isThroughCarry ? cpu.Status.C : Carry;
    cpu.Status.C = Carry;
}

FORCE_INLINE void GenericRotateRight(I8080 &cpu, bool isThroughCarry){
    const bool Carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= (isThroughCarry ? cpu.Status.C : Carry) << 7;
    cpu.Status.C = Carry;
}

FORCE_INLINE void I8080_RLC(Memory &memory, I8080 &cpu) {
    GenericRotateLeft(cpu, false);
}

FORCE_INLINE void I8080_RRC(Memory &memory, I8080 &cpu) {
    GenericRotateRight(cpu, false);
}

FORCE_INLINE void I8080_RAL(Memory &memory, I8080 &cpu) {
    GenericRotateLeft(cpu, true);
}

FORCE_INLINE void I8080_RAR(Memory &memory, I8080 &cpu) {
    GenericRotateRight(cpu, true);
}
