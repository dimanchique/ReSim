#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void GenericMOV_RegToReg(I8080 &cpu, BYTE& destRegister, BYTE& srcRegister){
    destRegister = srcRegister;
    cpu.cycles++;
}

FORCE_INLINE void GenericMOV_MemToReg(Memory &memory, I8080 &cpu, BYTE& destRegister){
    const WORD memoryAddress = I8080::SwapRegistersAsWord(cpu.H, cpu.L);
    cpu.cycles++;
    destRegister = cpu.ReadByte(memory, memoryAddress);
    cpu.cycles++;
}

FORCE_INLINE void GenericMOV_RegToMem(Memory &memory, I8080 &cpu, BYTE& srcRegister){
    const WORD memoryAddress = I8080::SwapRegistersAsWord(cpu.H, cpu.L);
    cpu.cycles++;
    cpu.WriteByte(memory, srcRegister, memoryAddress);
    cpu.cycles++;
}
