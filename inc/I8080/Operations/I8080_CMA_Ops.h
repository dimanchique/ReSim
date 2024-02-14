#pragma once
#include "I8080/I8080.h"

inline void I8080_CMA(Memory &memory, I8080 &cpu) {
    cpu.A = ~cpu.A;
}
