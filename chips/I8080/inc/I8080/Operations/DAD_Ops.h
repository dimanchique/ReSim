#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericDAD(I8080 &cpu, const WORD targetRegisterPtr) {
    WORD operand = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L); // we treat paired HL registers as a 16-bit WORD
    U32 result = operand + targetRegisterPtr;
    cpu.cycles += 4; // assuming it takes 4 cycles to do 16-bit add
    ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref((WORD)result, cpu.H, cpu.L);
    cpu.cycles += 2; // 2 more cycles to pass result to HL
    cpu.Status.C = (result >> 16) > 0;
}

void I8080_DAD_B(Memory &memory, I8080 &cpu) {
    GenericDAD(cpu, ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.B, cpu.C));
}

void I8080_DAD_D(Memory &memory, I8080 &cpu) {
    GenericDAD(cpu, ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E));
}

void I8080_DAD_H(Memory &memory, I8080 &cpu) {
    GenericDAD(cpu, ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L));
}

void I8080_DAD_SP(Memory &memory, I8080 &cpu) {
    GenericDAD(cpu, cpu.SP);
}
