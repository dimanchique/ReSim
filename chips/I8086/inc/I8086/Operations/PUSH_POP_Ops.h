#pragma once

#include "I8086/I8086.h"

FORCE_INLINE void PUSH_Reg(I8086& cpu, const BYTE regIdx) {
    assert(regIdx <= 7);
    cpu.PushDataToStack(*cpu.GetRegWordPtr(regIdx));
}

FORCE_INLINE void PUSH_SReg(I8086& cpu, const BYTE regIdx) {
    assert(regIdx <= 3);
    cpu.PushDataToStack(*cpu.GetSRegWordPtr(regIdx));
}

FORCE_INLINE void POP_Reg(I8086& cpu, const BYTE regIdx) {
    assert(regIdx <= 7);
    *cpu.GetRegWordPtr(regIdx) = cpu.PopDataFromStack();
}

FORCE_INLINE void POP_SReg(I8086& cpu, const BYTE regIdx) {
    assert(regIdx <= 3);
    *cpu.GetSRegWordPtr(regIdx) = cpu.PopDataFromStack();
}

void I8086_PUSH_Reg(BYTE OpCode, I8086 &cpu) {
    PUSH_Reg(cpu, OpCode - PUSH_AX);
}

void I8086_PUSH_SReg(BYTE OpCode, I8086 &cpu) {
    PUSH_SReg(cpu, (OpCode - PUSH_ES) / 8);
}

void I8086_PUSH_AX(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_CX(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_DX(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_BX(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_SP(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_BP(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_SI(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_DI(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_Reg(OpCode, cpu);
}

void I8086_PUSH_DS(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_SReg(OpCode, cpu);
}

void I8086_PUSH_CS(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_SReg(OpCode, cpu);
}

void I8086_PUSH_SS(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_SReg(OpCode, cpu);
}

void I8086_PUSH_ES(BYTE OpCode, I8086 &cpu) {
    I8086_PUSH_SReg(OpCode, cpu);
}

void I8086_POP_Reg(BYTE OpCode, I8086 &cpu) {
    POP_Reg(cpu, OpCode - POP_AX);
}

void I8086_POP_SReg(BYTE OpCode, I8086 &cpu) {
    POP_SReg(cpu, (OpCode - POP_ES) / 8);
}

void I8086_POP_AX(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_CX(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_DX(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_BX(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_SP(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_BP(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_SI(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_DI(BYTE OpCode, I8086 &cpu) {
    I8086_POP_Reg(OpCode, cpu);
}

void I8086_POP_DS(BYTE OpCode, I8086 &cpu) {
    I8086_POP_SReg(OpCode, cpu);
}

void I8086_POP_SS(BYTE OpCode, I8086 &cpu) {
    I8086_POP_SReg(OpCode, cpu);
}

void I8086_POP_ES(BYTE OpCode, I8086 &cpu) {
    I8086_POP_SReg(OpCode, cpu);
}
