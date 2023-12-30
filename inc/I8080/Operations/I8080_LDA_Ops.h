#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericLDA(Memory &memory, I8080 &cpu, WORD memoryAddress){
    const BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    cpu.cycles++;
    cpu.A = memoryValue;
    cpu.cycles++;
}

FORCE_INLINE void I8080_LDA(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    GenericLDA(memory, cpu, memoryAddress);
}

FORCE_INLINE void I8080_LDAX_B(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.B.AsBigEndianWord();
    GenericLDA(memory, cpu, memoryAddress);
}

FORCE_INLINE void I8080_LDAX_D(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.D.AsBigEndianWord();
    GenericLDA(memory, cpu, memoryAddress);
}
