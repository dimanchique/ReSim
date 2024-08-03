#pragma once
#include "I8080/I8080.h"

inline void I8080_XCHG(Memory &memory, I8080 &cpu) {
    const WORD valueD = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E);
    const WORD valueH = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(valueH, cpu.D, cpu.E);
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(valueD, cpu.H, cpu.L);
    cpu.cycles++;
}
