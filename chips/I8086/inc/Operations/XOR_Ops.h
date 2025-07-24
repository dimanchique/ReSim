#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformXOR(InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before ^ result.rightOp.before;
    result.rightOp.after = result.rightOp.before;
}

template<typename T>
void UpdateStatusAfterXOR(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterXOR_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterXOR(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_XOR(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformXOR, &UpdateStatusAfterXOR_Wrapper, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Mem8 XOR Reg8
void I8086_XOR_Eb_Gb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(cpu);
}

//  Mem16 <-- Mem16 XOR Reg16
void I8086_XOR_Ev_Gv(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(cpu);
}

//  Reg8 <-- Reg8 XOR Reg8
//  Reg8 <-- Reg8 XOR Mem8
void I8086_XOR_Gb_Eb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XOR<BYTE>(cpu);
}

//  Reg16 <-- Reg16 XOR Reg16
//  Reg16 <-- Reg16 XOR Mem16
void I8086_XOR_Gv_Ev(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_XOR<WORD>(cpu);
}

//  AL <-- AL XOR Immediate8
//  AX <-- AX XOR Immediate16
template<typename T>
void I8086_XOR_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> instruction_result{};
    instruction_result.leftOp.before = *regPtr;
    instruction_result.rightOp.before = value;
    PerformXOR(instruction_result);
    *regPtr = instruction_result.leftOp.after;
    UpdateStatusAfterOR(cpu, *regPtr);
}

//  AL <-- AL XOR Immediate8
void I8086_XOR_AL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_XOR_Ax_Ix(&cpu.AL, cpu);
}

//  AX <-- AX XOR Immediate16
void I8086_XOR_AX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_XOR_Ax_Ix(&cpu.AX, cpu);
}

//  Reg8/16 <-- Reg8/16 XOR Immediate8/16
//  Mem8/16 <-- Mem8/16 XOR Immediate8/16
template<typename T>
void I8086_XOR_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformXOR, &UpdateStatusAfterXOR_Wrapper);
}
