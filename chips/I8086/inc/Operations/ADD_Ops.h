#pragma once
#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformADD(InstructionResult<T>& result) {
    const T before = result.leftOp.before;
    const T value = result.rightOp.before;
    result.leftOp.after = before + value;
    result.rightOp.after = value; // Preserve source operand

    // Calculate flags
    result.status.C = (result.leftOp.after < before); // Carry
    result.status.A = ((before & 0xF) + (value & 0xF)) > 0xF; // Auxiliary
    result.status.O = ((before ^ ~value) & (before ^ result.leftOp.after)) >> (sizeof(T)*8-1); // Overflow
}

template<typename T>
void UpdateStatusAfterADD(I8086 &cpu, const InstructionResult<T> &result) {
    cpu.Status.C = result.status.C;
    cpu.Status.A = result.status.A;
    cpu.Status.O = result.status.O;
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_ADD(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformADD, &UpdateStatusAfterADD, InstructionDirection::MemReg_Reg, RightToLeft);
}

// Mem8 <-- Mem8 + Reg8
void I8086_ADD_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_ADD<BYTE>(cpu);
}

// Mem16 <-- Mem16 + Reg16
void I8086_ADD_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_ADD<WORD>(cpu);
}

// Reg8 <-- Reg8 + Reg8/Mem8
void I8086_ADD_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_ADD<BYTE>(cpu);
}

// Reg16 <-- Reg16 + Reg16/Mem16
void I8086_ADD_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_ADD<WORD>(cpu);
}

// Immediate variants
template<typename T>
void I8086_ADD_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> result{};
    result.leftOp.before = *regPtr;
    result.rightOp.before = value;
    PerformADD(result);
    *regPtr = result.leftOp.after;
    UpdateStatusAfterADD(cpu, result);
}

// AL <-- AL + Immediate8
void I8086_ADD_AL_Ib(BYTE, I8086 &cpu) {
    I8086_ADD_Ax_Ix(&cpu.AL, cpu);
}

// AX <-- AX + Immediate16
void I8086_ADD_AX_Iv(BYTE, I8086 &cpu) {
    I8086_ADD_Ax_Ix(&cpu.AX, cpu);
}

// Memory/Register + Immediate
template<typename T>
void I8086_ADD_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformADD, &UpdateStatusAfterADD);
}
