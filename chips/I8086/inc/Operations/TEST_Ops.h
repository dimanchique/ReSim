#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformTEST(InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before & result.rightOp.before;
}

template<typename T>
void UpdateStatusAfterTEST(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterTEST_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterTEST(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_TEST(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformTEST, &UpdateStatusAfterTEST_Wrapper, InstructionDirection::MemReg_Reg, RightToLeft, false);
}

//  Mem8 TEST Reg8
void I8086_TEST_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_TEST<BYTE>(cpu);
}

//  Mem16 TEST Reg16
void I8086_TEST_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_TEST<WORD>(cpu);
}

//  Reg8 TEST Reg8
//  Reg8 TEST Mem8
void I8086_TEST_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_TEST<BYTE>(cpu);
}

//  Reg16 TEST Reg16
//  Reg16 TEST Mem16
void I8086_TEST_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_TEST<WORD>(cpu);
}

//  AL TEST Immediate8
//  AX TEST Immediate16
template<typename T>
void I8086_TEST_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> instruction_result{};
    instruction_result.leftOp.before = *regPtr;
    instruction_result.rightOp.before = value;
    PerformTEST(instruction_result);
    UpdateStatusAfterTEST(cpu, instruction_result.leftOp.after);
}

//  AL TEST Immediate8
void I8086_TEST_AL_Ib(BYTE, I8086 &cpu) {
    I8086_TEST_Ax_Ix(&cpu.AL, cpu);
}

//  AX TEST Immediate16
void I8086_TEST_AX_Iv(BYTE, I8086 &cpu) {
    I8086_TEST_Ax_Ix(&cpu.AX, cpu);
}

//  Reg8/16 TEST Immediate8/16
//  Mem8/16 TEST Immediate8/16
template<typename T>
void I8086_TEST_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformTEST, &UpdateStatusAfterTEST_Wrapper);
}
