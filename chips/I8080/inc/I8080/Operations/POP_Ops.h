#pragma once
#include "I8080/I8080.h"

void I8080_POP_B(Memory &memory, I8080 &cpu) {
    cpu.PopDataOffStack(memory, &cpu.B, &cpu.C);
}

void I8080_POP_D(Memory &memory, I8080 &cpu) {
    cpu.PopDataOffStack(memory, &cpu.D, &cpu.E);
}

void I8080_POP_H(Memory &memory, I8080 &cpu) {
    cpu.PopDataOffStack(memory, &cpu.H, &cpu.L);
}

void I8080_POP_PSW(Memory &memory, I8080 &cpu) {
    cpu.PopDataOffStack(memory, &cpu.A, (BYTE*)&cpu.Status);
}
