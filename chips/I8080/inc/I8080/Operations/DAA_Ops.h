#pragma once
#include "I8080/I8080.h"

void I8080_DAA(Memory &memory, I8080 &cpu) {
    BYTE slice = cpu.A & 0xF;
    if (slice > 9 || cpu.Status.AC)
    {
        cpu.A += 6;
        slice += 6;
        cpu.Status.AC = slice >> 4;
    }

    slice = (cpu.A >> 4) & 0xF;
    if (slice > 9 || cpu.Status.C)
    {
        slice += 6;
        cpu.Status.C = slice >> 4;
        slice &= 0xF;
        cpu.A &= 0xF;
        slice <<= 4;
        cpu.A |= slice;
    }
}
