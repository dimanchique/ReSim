#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_RZ(Memory &memory, I8080 &cpu) {
    if (cpu.Status.Z)
        cpu.PopProgramCounterOffStack(memory);
}
