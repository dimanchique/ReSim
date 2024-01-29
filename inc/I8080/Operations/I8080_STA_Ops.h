#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericSTA(Memory &memory, I8080 &cpu, WORD memoryAddress) {
    cpu.WriteByte(memory, cpu.A, memoryAddress);
}

FORCE_INLINE void I8080_STA(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    GenericSTA(memory, cpu, memoryAddress);
}

FORCE_INLINE void I8080_STAX_B(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.B, cpu.C);
    GenericSTA(memory, cpu, memoryAddress);
}

FORCE_INLINE void I8080_STAX_D(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = I8080::wordRegisterAsWordSwapped(cpu.D, cpu.E);
    GenericSTA(memory, cpu, memoryAddress);
}
