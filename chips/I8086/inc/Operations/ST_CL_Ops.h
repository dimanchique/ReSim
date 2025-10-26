#pragma once

#include "I8086.h"

void I8086_CLC(BYTE, I8086 &cpu) {
    cpu.Status.C = 0;
}

void I8086_STC(BYTE, I8086 &cpu) {
    cpu.Status.C = 1;
}

void I8086_CLI(BYTE, I8086 &cpu) {
    cpu.Status.I = 0;
}

void I8086_CMC(BYTE, I8086 &cpu) {
    cpu.Status.C = !cpu.Status.C;
}

void I8086_STI(BYTE, I8086 &cpu) {
    cpu.Status.I = 1;
}

void I8086_CLD(BYTE, I8086 &cpu) {
    cpu.Status.D = 0;
}

void I8086_STD(BYTE, I8086 &cpu) {
    cpu.Status.D = 1;
}
