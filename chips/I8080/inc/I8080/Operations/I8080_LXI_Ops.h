#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericLXI(Memory &memory, I8080 &cpu, WORD* targetRegisterPtr) {
    const WORD immediateValue = cpu.FetchWord(memory);
    *targetRegisterPtr = immediateValue;
}

FORCE_INLINE void I8080_LXI_B(Memory &memory, I8080 &cpu) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.B);
    GenericLXI(memory, cpu, registerPtr);
}

FORCE_INLINE void I8080_LXI_D(Memory &memory, I8080 &cpu) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.D);
    GenericLXI(memory, cpu, registerPtr);
}

FORCE_INLINE void I8080_LXI_H(Memory &memory, I8080 &cpu) {
    WORD* registerPtr = I8080::wordRegisterAsWordUnswapped(cpu.H);
    GenericLXI(memory, cpu, registerPtr);
}

FORCE_INLINE void I8080_LXI_SP(Memory &memory, I8080 &cpu) {
    GenericLXI(memory, cpu, &cpu.SP);
}
