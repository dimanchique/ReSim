#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericMOV_RegToReg(I8080 &cpu, BYTE &destRegister, const BYTE &srcRegister) {
    destRegister = srcRegister;
    cpu.cycles++;
}

FORCE_INLINE void GenericMOV_MemToReg(Memory &memory, I8080 &cpu, BYTE &destRegister) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    destRegister = cpu.ReadByte(memory, memoryAddress);
}

FORCE_INLINE void GenericMOV_RegToMem(Memory &memory, I8080 &cpu, const BYTE &srcRegister) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.WriteByte(memory, srcRegister, memoryAddress);
}
