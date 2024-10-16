#pragma once
#include "I8080/I8080.h"

void I8080_PCHL(Memory &memory, I8080 &cpu) {
    const WORD targetAddr = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.PC = targetAddr;
    cpu.cycles++;
}
