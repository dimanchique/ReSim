#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_SHLD(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    const WORD storeValue = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    cpu.WriteWord(memory, storeValue, memoryAddress);
}
