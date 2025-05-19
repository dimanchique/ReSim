#pragma once

#include "I8086/I8086.h"

template<typename T>
FORCE_INLINE void I8086_MOV_Ax_0x(I8086 &cpu, T &targetRegister, InstructionDirection direction) {
    const WORD directAddress = cpu.Fetch<WORD>();
    const DWORD effectiveAddress = EFFECTIVE_ADDRESS(directAddress, cpu.DS);

    if (direction == InstructionDirection::MemReg_Reg)
        targetRegister = cpu.Read<T>(effectiveAddress);
    else
        cpu.Write(effectiveAddress, targetRegister);
}

void I8086_MOV_AL_Ob(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ax_0x(cpu, cpu.AL, InstructionDirection::MemReg_Reg);
}

void I8086_MOV_AX_Ov(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ax_0x(cpu, cpu.AX, InstructionDirection::MemReg_Reg);
}

void I8086_MOV_Ob_AL(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ax_0x(cpu, cpu.AL, InstructionDirection::Reg_MemReg);
}

void I8086_MOV_Ov_AX(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ax_0x(cpu, cpu.AX, InstructionDirection::Reg_MemReg);
}
