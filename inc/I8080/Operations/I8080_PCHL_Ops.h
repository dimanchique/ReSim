#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_PCHL(Memory &memory, I8080 &cpu) {
    const WORD targetAddr = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    cpu.PC = targetAddr;
    cpu.cycles++;
}
