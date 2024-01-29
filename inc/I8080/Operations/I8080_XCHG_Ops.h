#pragma once
#include "I8080/I8080.h"

inline void I8080_XCHG(Memory &memory, I8080 &cpu) {
    const WORD valueD = cpu.wordRegisterAsWordSwapped(cpu.D, cpu.E);
    const WORD valueH = cpu.wordRegisterAsWordSwapped(cpu.H, cpu.L);
    cpu.wordToRegisterSwapped(valueH, cpu.D, cpu.E);
    cpu.wordToRegisterSwapped(valueD, cpu.H, cpu.L);
    cpu.cycles++;
}
