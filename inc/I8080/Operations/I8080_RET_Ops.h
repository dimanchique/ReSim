#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_RET(Memory &memory, I8080 &cpu) {
    cpu.PopProgramCounterOffStack(memory);
}
