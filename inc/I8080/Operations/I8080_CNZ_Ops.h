#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_CNZ(Memory &memory, I8080 &cpu) {
    const WORD newPC = cpu.FetchWord(memory);
    if (!cpu.Status.Z) {
        cpu.PushProgramCounterOntoStack(memory);
        cpu.PC = newPC;
    }
    cpu.cycles++;
}
