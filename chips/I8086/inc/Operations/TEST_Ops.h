#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformTEST(I8086& cpu, InstructionResult<T>& result) {
    result.leftOp.after = result.leftOp.before & result.rightOp.before;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_TEST(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformTEST, InstructionDirection::MemReg_Reg, RightToLeft, false);
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
    PerformTEST(cpu, instruction_result);
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
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformTEST);
}
