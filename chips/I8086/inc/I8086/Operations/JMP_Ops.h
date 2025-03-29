#pragma once

#include "I8086/I8086.h"

FORCE_INLINE void PerformJump(I8086 &cpu, const bool conditionFlag = true) {
    const SWORD disp = cpu.Fetch<WORD>();
    if (conditionFlag)
        cpu.PC += disp;
}

void I8086_JO_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.O);
}

void I8086_JNO_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.O);
}

void I8086_JB_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.C);
}

void I8086_JNB_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.C);
}

void I8086_JZ_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.Z);
}

void I8086_JNZ_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.Z);
}

void I8086_JBE_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, (cpu.Status.Z || cpu.Status.C));
}

void I8086_JA_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !(cpu.Status.Z || cpu.Status.C));
}

void I8086_JS_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.S);
}

void I8086_JNS_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.S);
}

void I8086_JPE_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, cpu.Status.P);
}

void I8086_JPO_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !cpu.Status.P);
}

void I8086_JL_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, (cpu.Status.S ^ cpu.Status.O));
}

void I8086_JGE_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !(cpu.Status.S ^ cpu.Status.O));
}

void I8086_JLE_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, ((cpu.Status.S ^ cpu.Status.O) || cpu.Status.Z));
}

void I8086_JG_Jb(BYTE OpCode, I8086 &cpu) {
    PerformJump(cpu, !((cpu.Status.S ^ cpu.Status.O) || cpu.Status.Z));
}
