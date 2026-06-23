#pragma once
#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformSUB(I8086& cpu, InstructionResult<T>& result) {
    const T before = result.leftOp.before;
    const T value = ~result.rightOp.before + 1; // two's complement
    result.leftOp.after = before + value;
    result.rightOp.after = result.rightOp.before; // Preserve source operand

    // Calculate flags
    cpu.Status.C = before < result.rightOp.before; // Carry
    cpu.Status.A = (before & 0xF) < (result.rightOp.before & 0xF); // Auxiliary
    cpu.Status.O = ((before ^ result.rightOp.before) & (before ^ result.leftOp.after)) >> (sizeof(T)*8-1); // Overflow
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_SUB(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformSUB, InstructionDirection::MemReg_Reg, RightToLeft);
}

// Mem8 <-- Mem8 - Reg8
void I8086_SUB_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SUB<BYTE>(cpu);
}

// Mem16 <-- Mem16 - Reg16
void I8086_SUB_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SUB<WORD>(cpu);
}

// Reg8 <-- Reg8 - Reg8/Mem8
void I8086_SUB_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SUB<BYTE>(cpu);
}

// Reg16 <-- Reg16 - Reg16/Mem16
void I8086_SUB_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_SUB<WORD>(cpu);
}

// Immediate variants
template<typename T>
void I8086_SUB_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> result{};
    result.leftOp.before = *regPtr;
    result.rightOp.before = value;
    PerformSUB(cpu, result);
    *regPtr = result.leftOp.after;
}

// AL <-- AL - Immediate8
void I8086_SUB_AL_Ib(BYTE, I8086 &cpu) {
    I8086_SUB_Ax_Ix(&cpu.AL, cpu);
}

// AX <-- AX - Immediate16
void I8086_SUB_AX_Iv(BYTE, I8086 &cpu) {
    I8086_SUB_Ax_Ix(&cpu.AX, cpu);
}

// Memory/Register - Immediate
template<typename T>
void I8086_SUB_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformSUB);
}
