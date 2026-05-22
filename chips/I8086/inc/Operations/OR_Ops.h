#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformOR(I8086& cpu, InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before | result.rightOp.before;
    result.rightOp.after = result.rightOp.before;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_OR(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformOR, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Mem8 OR Reg8
void I8086_OR_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(cpu);
}

//  Mem16 <-- Mem16 OR Reg16
void I8086_OR_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(cpu);
}

//  Reg8 <-- Reg8 OR Reg8
//  Reg8 <-- Reg8 OR Mem8
void I8086_OR_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_OR<BYTE>(cpu);
}

//  Reg16 <-- Reg16 OR Reg16
//  Reg16 <-- Reg16 OR Mem16
void I8086_OR_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_OR<WORD>(cpu);
}

//  AL <-- AL OR Immediate8
//  AX <-- AX OR Immediate16
template<typename T>
void I8086_OR_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> instruction_result{};
    instruction_result.leftOp.before = *regPtr;
    instruction_result.rightOp.before = value;
    PerformOR(cpu, instruction_result);
    *regPtr = instruction_result.leftOp.after;
}

//  AL <-- AL OR Immediate8
void I8086_OR_AL_Ib(BYTE, I8086 &cpu) {
    I8086_OR_Ax_Ix(&cpu.AL, cpu);
}

//  AX <-- AX OR Immediate16
void I8086_OR_AX_Iv(BYTE, I8086 &cpu) {
    I8086_OR_Ax_Ix(&cpu.AX, cpu);
}

//  Reg8/16 <-- Reg8/16 OR Immediate8/16
//  Mem8/16 <-- Mem8/16 OR Immediate8/16
template<typename T>
void I8086_OR_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformOR);
}
