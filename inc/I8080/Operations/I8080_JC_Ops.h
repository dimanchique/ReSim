#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_JC(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    if (cpu.Status.C)
        cpu.PC = memoryAddress;
}
