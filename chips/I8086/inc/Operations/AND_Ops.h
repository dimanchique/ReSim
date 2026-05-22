#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformAND(I8086& cpu, InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before & result.rightOp.before;
    result.rightOp.after = result.rightOp.before;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_AND(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformAND, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Mem8 AND Reg8
void I8086_AND_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(cpu);
}

//  Mem16 <-- Mem16 AND Reg16
void I8086_AND_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_AND<WORD>(cpu);
}

//  Reg8 <-- Reg8 AND Reg8
//  Reg8 <-- Reg8 AND Mem8
void I8086_AND_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(cpu);
}

//  Reg16 <-- Reg16 AND Reg16
//  Reg16 <-- Reg16 AND Mem16
void I8086_AND_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_AND<WORD>(cpu);
}

//  AL <-- AL AND Immediate8
//  AX <-- AX AND Immediate16
template<typename T>
void I8086_AND_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> instruction_result{};
    instruction_result.leftOp.before = *regPtr;
    instruction_result.rightOp.before = value;
    PerformAND(cpu, instruction_result);
    *regPtr = instruction_result.leftOp.after;
}

//  AL <-- AL AND Immediate8
void I8086_AND_AL_Ib(BYTE, I8086 &cpu) {
    I8086_AND_Ax_Ix(&cpu.AL, cpu);
}

//  AX <-- AX AND Immediate16
void I8086_AND_AX_Iv(BYTE, I8086 &cpu) {
    I8086_AND_Ax_Ix(&cpu.AX, cpu);
}

//  Reg8/16 <-- Reg8/16 AND Immediate8/16
//  Mem8/16 <-- Mem8/16 AND Immediate8/16
template<typename T>
void I8086_AND_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformAND);
}
