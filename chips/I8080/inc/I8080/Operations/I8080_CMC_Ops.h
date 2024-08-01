#pragma once
#include "I8080/I8080.h"

inline void I8080_CMC(Memory &memory, I8080 &cpu) {
    cpu.Status.C = !cpu.Status.C;
}
