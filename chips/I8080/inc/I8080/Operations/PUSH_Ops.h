#pragma once
#include "I8080/I8080.h"

void I8080_PUSH_B(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.B, cpu.C);
}

void I8080_PUSH_D(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.D, cpu.E);
}

void I8080_PUSH_H(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.H, cpu.L);
}

void I8080_PUSH_PSW(Memory &memory, I8080 &cpu) {
    cpu.PushDataOntoStack(memory, cpu.A, cpu.Status);
}
