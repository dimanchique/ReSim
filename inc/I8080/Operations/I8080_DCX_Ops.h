#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericDCX(I8080 &cpu, WORD *targetRegisterPtr) {
    (*targetRegisterPtr)--;
    cpu.cycles++;
}

FORCE_INLINE void I8080_DCX_B(Memory &memory, I8080 &cpu) {
    GenericDCX(cpu, reinterpret_cast<WORD*>(&cpu.B));
}

FORCE_INLINE void I8080_DCX_D(Memory &memory, I8080 &cpu) {
    GenericDCX(cpu, reinterpret_cast<WORD*>(&cpu.D));
}

FORCE_INLINE void I8080_DCX_H(Memory &memory, I8080 &cpu) {
    GenericDCX(cpu, reinterpret_cast<WORD*>(&cpu.H));
}

FORCE_INLINE void I8080_DCX_SP(Memory &memory, I8080 &cpu) {
    GenericDCX(cpu, &cpu.SP);
}
