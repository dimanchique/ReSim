#pragma once
#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformCMP(I8086& cpu, InstructionResult<T>& result) {
    const T before = result.leftOp.before;
    const T value = result.rightOp.before;

    const DWORD fullResult = (DWORD)before - value;
    result.leftOp.after = (T)fullResult;
    result.rightOp.after = value;

    cpu.Status.C = before < value;
    cpu.Status.A = ((before & 0xF) - (value & 0xF)) < 0;
    cpu.Status.O = ((before ^ value) & (before ^ result.leftOp.after)) >> (sizeof(T)*8-1);
    cpu.Status.UpdateStatusByValue(result.leftOp.after, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void I8086_EGx_EGx_CMP(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformCMP, InstructionDirection::MemReg_Reg, RightToLeft, false);
}

// Mem8 <-- Mem8 - Reg8 (flags only, no write)
void I8086_CMP_Eb_Gb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_CMP<BYTE>(cpu);
}

// Mem16 <-- Mem16 - Reg16 (flags only, no write)
void I8086_CMP_Ev_Gv(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_CMP<WORD>(cpu);
}

// Reg8 <-- Reg8 - Reg8/Mem8 (flags only, no write)
void I8086_CMP_Gb_Eb(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_CMP<BYTE>(cpu);
}

// Reg16 <-- Reg16 - Reg16/Mem16 (flags only, no write)
void I8086_CMP_Gv_Ev(BYTE, I8086 &cpu) {
    I8086_EGx_EGx_CMP<WORD>(cpu);
}

// Immediate variants
template<typename T>
void I8086_CMP_Ax_Ix(T* regPtr, I8086 &cpu) {
    const T value = cpu.Fetch<T>();
    InstructionResult<T> result{};
    result.leftOp.before = *regPtr;
    result.rightOp.before = value;
    PerformCMP(cpu, result);
    // No result stored back - flags only
}

// AL <-- AL - Immediate8 (flags only, no write)
void I8086_CMP_AL_Ib(BYTE, I8086 &cpu) {
    I8086_CMP_Ax_Ix(&cpu.AL, cpu);
}

// AX <-- AX - Immediate16 (flags only, no write)
void I8086_CMP_AX_Iv(BYTE, I8086 &cpu) {
    I8086_CMP_Ax_Ix(&cpu.AX, cpu);
}

// Memory/Register - Immediate (flags only, no write)
template<typename T>
void I8086_CMP_Ex_Ix(I8086 &cpu, const ModRegByte &modRegByte) {
    I8086_Ex_Ix<T>(cpu, modRegByte, &PerformCMP, false);
}
