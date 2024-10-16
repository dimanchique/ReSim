#pragma once
#include "I8080/I8080.h"

void I8080_SPHL(Memory &memory, I8080 &cpu) {
    cpu.SP = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.cycles++;
}
