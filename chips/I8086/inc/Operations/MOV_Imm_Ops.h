#pragma once

#include "I8086.h"

FORCE_INLINE void I8086_MOV_Ib(BYTE OpCode, I8086 &cpu) {
    const BYTE regIdx = OpCode - MOV_AL_Ib;
    assert(regIdx <= 7);

    const BYTE immValue = cpu.Fetch<BYTE>();
    *cpu.GetRegBytePtr(regIdx) = immValue;
}

FORCE_INLINE void I8086_MOV_Iv(BYTE OpCode, I8086 &cpu) {
    const BYTE regIdx = OpCode - MOV_AX_Iv;
    assert(regIdx <= 7);

    const WORD immValue = cpu.Fetch<WORD>();
    *cpu.GetRegWordPtr(regIdx) = immValue;
}

void I8086_MOV_AL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_CL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_DL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_BL_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_AH_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_CH_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_DH_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_BH_Ib(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Ib(OpCode, cpu);
}

void I8086_MOV_AX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_CX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_DX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_BX_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_SP_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_BP_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_SI_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

void I8086_MOV_DI_Iv(BYTE OpCode, I8086 &cpu) {
    I8086_MOV_Iv(OpCode, cpu);
}

//  Reg <-- Immediate8
void I8086_MOV_Eb_Ib(BYTE, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    I8086_Ex_Ix<BYTE>(cpu, modReg, &PerformMOV, &UpdateStatusAfterMOV_Wrapper);
}

//  Reg <-- Immediate16
void I8086_MOV_Ev_Iv(BYTE, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    I8086_Ex_Ix<WORD>(cpu, modReg, &PerformMOV, &UpdateStatusAfterMOV_Wrapper);
}
