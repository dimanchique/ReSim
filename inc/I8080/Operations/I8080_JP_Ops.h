#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_JP(Memory &memory, I8080 &cpu) {
    const WORD newPC = cpu.FetchWord(memory);
    if (!cpu.Status.S)
        cpu.PC = newPC;
}
