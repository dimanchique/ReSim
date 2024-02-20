#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_RC(Memory &memory, I8080 &cpu) {
    if (cpu.Status.C)
        cpu.PopProgramCounterOffStack(memory);
}
