#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_PUSH_B(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.B, cpu.C);
}

FORCE_INLINE void I8080_PUSH_D(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.D, cpu.E);
}

FORCE_INLINE void I8080_PUSH_H(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.H, cpu.L);
}

FORCE_INLINE void I8080_PUSH_PSW(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.A, cpu.Status);
}
