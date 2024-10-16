#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericLDA(Memory &memory, I8080 &cpu, const WORD memoryAddress) {
    const BYTE memoryValue = cpu.ReadByte(memory, memoryAddress);
    cpu.A = memoryValue;
}

void I8080_LDA(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord(memory);
    GenericLDA(memory, cpu, memoryAddress);
}

void I8080_LDAX_B(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.B, cpu.C);
    GenericLDA(memory, cpu, memoryAddress);
}

void I8080_LDAX_D(Memory &memory, I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E);
    GenericLDA(memory, cpu, memoryAddress);
}
