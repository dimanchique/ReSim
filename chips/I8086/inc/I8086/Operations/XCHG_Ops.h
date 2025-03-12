#pragma once

#include "I8086/I8086.h"
#include "Adressing.h"

template<typename T>
FORCE_INLINE void PerformXCHG(InstructionResult<T>& result) {
    result.leftOp.after = result.rightOp.before;
    result.rightOp.after = result.leftOp.before;
}

template<typename T>
void I8086_EGx_EGx_XCHG(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformXCHG, nullptr, InstructionDirection::MemReg_Reg, Bidirectional);
}

//  Mem8/Reg8 <--> Mem8/Reg8
void I8086_XCHG_Gb_Eb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XCHG<BYTE>(cpu);
}

//  Mem16/Reg16 <--> Mem16/Reg16
void I8086_XCHG_Gv_Ev(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XCHG<WORD>(cpu);
}


FORCE_INLINE void PerformXCHG_AX(I8086 &cpu, WORD* regPtr) {
    WORD tmp = cpu.AX;
    cpu.AX = *regPtr;
    *regPtr = tmp;
}

void I8086_XCHG_CX_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.CX);
}

void I8086_XCHG_DX_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.DX);
}

void I8086_XCHG_BX_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.BX);
}

void I8086_XCHG_SP_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.SP);
}

void I8086_XCHG_BP_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.BP);
}

void I8086_XCHG_SI_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.SI);
}

void I8086_XCHG_DI_AX(BYTE OpCode, I8086 &cpu) {
    PerformXCHG_AX(cpu, &cpu.DI);
}
