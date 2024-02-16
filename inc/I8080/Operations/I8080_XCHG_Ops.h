#pragma once
#include "I8080/I8080.h"

inline void I8080_XCHG(Memory &memory, I8080 &cpu) {
    const WORD valueD = I8080::wordRegisterAsWordSwapped(cpu.D, cpu.E);
    const WORD valueH = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    I8080::wordToRegisterSwapped(valueH, cpu.D, cpu.E);
    I8080::wordToRegisterSwapped(valueD, cpu.H, cpu.L);
    cpu.cycles++;
}
