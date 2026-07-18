#pragma once

#include "I8086.h"

void I8086_JMP_Ap(BYTE, I8086 &cpu) {
    const WORD offset = cpu.Fetch<WORD>();
    const WORD segmentBase = cpu.Fetch<WORD>();

    cpu.PC = offset;
    cpu.CS = segmentBase;
}

template<typename T, typename U>
void I8086_JMP_Jx(I8086 &cpu) {
    const U displacement = (U)cpu.Fetch<T>();
    cpu.PC += displacement;
}

void I8086_JMP_Jv(BYTE, I8086 &cpu) {
    I8086_JMP_Jx<WORD, SWORD>(cpu); // read WORD cast to SWORD
}

void I8086_JMP_Jb(BYTE, I8086 &cpu) {
    I8086_JMP_Jx<BYTE, SBYTE>(cpu); // read BYTE cast to SBYTE
}

void JMP_GRP5(I8086& cpu, const ModRegByte& modReg) {
    const OperandSize opSize = OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(opSize, InstructionDirection::MemReg_Imm, modReg);
    WORD newPC = instructionData.leftOp.get(cpu);

    cpu.PC = newPC;
}

void JMP_GRP5_MP(I8086& cpu, const ModRegByte& modReg) {
    const OperandSize opSize = OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(opSize, InstructionDirection::MemReg_Imm, modReg);
    WORD newPC = instructionData.leftOp.get(cpu);

    cpu.PC = newPC;
}

FORCE_INLINE void PerformJump(I8086 &cpu, const bool conditionFlag = true) {
    const SBYTE disp = (SBYTE)cpu.Fetch<BYTE>();
    if (conditionFlag)
        cpu.PC += disp;
}

void I8086_JO_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.O);
}

void I8086_JNO_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.O);
}

void I8086_JB_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.C);
}

void I8086_JNB_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.C);
}

void I8086_JZ_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.Z);
}

void I8086_JNZ_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.Z);
}

void I8086_JBE_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, (cpu.Status.Z || cpu.Status.C));
}

void I8086_JA_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !(cpu.Status.Z || cpu.Status.C));
}

void I8086_JS_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.S);
}

void I8086_JNS_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.S);
}

void I8086_JPE_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.P);
}

void I8086_JPO_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.P);
}

void I8086_JL_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, (cpu.Status.S ^ cpu.Status.O));
}

void I8086_JGE_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !(cpu.Status.S ^ cpu.Status.O));
}

void I8086_JLE_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, ((cpu.Status.S ^ cpu.Status.O) || cpu.Status.Z));
}

void I8086_JG_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, !((cpu.Status.S ^ cpu.Status.O) || cpu.Status.Z));
}

void I8086_JCXZ_Jb(BYTE, I8086 &cpu) {
    PerformJump(cpu, cpu.CX == 0);
}
