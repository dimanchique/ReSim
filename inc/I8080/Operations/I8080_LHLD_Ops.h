#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void I8080_LHLD(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    const WORD memoryValue = cpu.ReadWord(memory, memoryAddress);
    cpu.L = memoryValue & 0xFF;
    cpu.H = (memoryValue >> 8) & 0xFF;
}
