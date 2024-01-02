#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericINX(I8080 &cpu, WORD* targetRegisterPtr){
    (*targetRegisterPtr)++;
    cpu.cycles++;
}

FORCE_INLINE void I8080_INX_B(Memory &memory, I8080 &cpu) {
    GenericINX(cpu, reinterpret_cast<WORD*>(&cpu.B));
}

FORCE_INLINE void I8080_INX_D(Memory &memory, I8080 &cpu) {
    GenericINX(cpu, reinterpret_cast<WORD*>(&cpu.D));
}

FORCE_INLINE void I8080_INX_H(Memory &memory, I8080 &cpu) {
    GenericINX(cpu, reinterpret_cast<WORD*>(&cpu.H));
}

FORCE_INLINE void I8080_INX_SP(Memory &memory, I8080 &cpu) {
    GenericINX(cpu, &cpu.SP);
}
