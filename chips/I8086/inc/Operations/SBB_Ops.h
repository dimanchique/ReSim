#pragma once
#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformSBB(I8086& cpu, InstructionResult<T>& result) {
    const T before = result.leftOp.before;
    const T value = result.rightOp.before;
    const BYTE oldC = cpu.Status.C;

    const DWORD fullResult = (DWORD)before - value - oldC;
    result.leftOp.after = (T)fullResult;
    result.rightOp.after = value;

    cpu.Status.C = before < (DWORD)value + oldC; // Borrow
    cpu.Status.A = ((before & 0xF) - (value & 0xF) - oldC) < 0; // Auxiliary
    cpu.Status.O = ((before ^ value) & (before ^ result.leftOp.after)) >> (sizeof(T)*8-1); // Overflow
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_SBB(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformSBB, InstructionDirection::MemReg_Reg, RightToLeft);
}

// Mem8 <-- Mem8 - Reg8 - Borrow
void I8086_SBB_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SBB<BYTE>(cpu);
}

// Mem16 <-- Mem16 - Reg16 - Borrow
void I8086_SBB_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SBB<WORD>(cpu);
}

// Reg8 <-- Reg8 - Reg8/Mem8 - Borrow
void I8086_SBB_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SBB<BYTE>(cpu);
}

// Reg16 <-- Reg16 - Reg16/Mem16 - Borrow
void I8086_SBB_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SBB<WORD>(cpu);
}

// Immediate variants
template<typename T>
void I8086_SBB_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> result{};
    result.leftOp.before = *regPtr;
    result.rightOp.before = value;
    PerformSBB(cpu, result);
    *regPtr = result.leftOp.after;
}

// AL <-- AL - Immediate8 - Borrow
void I8086_SBB_AL_Ib(BYTE, I8086 &cpu) {
    I8086_SBB_Ax_Ix(&cpu.AL, cpu);
}

// AX <-- AX - Immediate16 - Borrow
void I8086_SBB_AX_Iv(BYTE, I8086 &cpu) {
    I8086_SBB_Ax_Ix(&cpu.AX, cpu);
}

// Memory/Register - Immediate - Borrow
template<typename T>
void I8086_SBB_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformSBB);
}
