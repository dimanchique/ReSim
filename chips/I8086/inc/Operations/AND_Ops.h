#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformAND(InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before & result.rightOp.before;
    result.rightOp.after = result.rightOp.before;
}

template<typename T>
void UpdateStatusAfterAND(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterAND_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterAND(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_AND(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformAND, &UpdateStatusAfterAND_Wrapper, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Mem8 AND Reg8
void I8086_AND_Eb_Gb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(cpu);
}

//  Mem16 <-- Mem16 AND Reg16
void I8086_AND_Ev_Gv(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_AND<WORD>(cpu);
}

//  Reg8 <-- Reg8 AND Reg8
//  Reg8 <-- Reg8 AND Mem8
void I8086_AND_Gb_Eb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_AND<BYTE>(cpu);
}

//  Reg16 <-- Reg16 AND Reg16
//  Reg16 <-- Reg16 AND Mem16
void I8086_AND_Gv_Ev(BYTE OpCode, I8086 &cpu) {
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
    PerformAND(instruction_result);
    *regPtr = instruction_result.leftOp.after;
    UpdateStatusAfterAND(cpu, *regPtr);
}

//  AL <-- AL AND Immediate8
void I8086_AND_AL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_AND_Ax_Ix(&cpu.AL, cpu);
}

//  AX <-- AX AND Immediate16
void I8086_AND_AX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_AND_Ax_Ix(&cpu.AX, cpu);
}

//  Reg8/16 <-- Reg8/16 AND Immediate8/16
//  Mem8/16 <-- Mem8/16 AND Immediate8/16
template<typename T>
void I8086_AND_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformAND, &UpdateStatusAfterAND_Wrapper);
}
