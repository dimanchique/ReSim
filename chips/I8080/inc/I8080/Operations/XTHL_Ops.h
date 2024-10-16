#pragma once
#include "I8080/I8080.h"

void I8080_XTHL(Memory &memory, I8080 &cpu) {
    const WORD stackPointerValue = cpu.ReadWord(memory, cpu.SP);
    const WORD registerValue = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.cycles++;
    cpu.WriteWord(memory, registerValue, cpu.SP);
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(stackPointerValue, cpu.H, cpu.L);
    cpu.cycles++;
}
