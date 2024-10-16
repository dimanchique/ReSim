#pragma once
#include "I8080/I8080.h"

void I8080_JMP(Memory &memory, I8080 &cpu) {
    cpu.PC = cpu.FetchWord(memory);
}

FORCE_INLINE void GenericJump_Conditional(Memory &memory, I8080 &cpu, const bool &conditionFlag) {
    const WORD newPC = cpu.FetchWord(memory);
    if (conditionFlag)
        cpu.PC = newPC;
}

void I8080_JC(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, cpu.Status.C);
}

void I8080_JNC(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, !cpu.Status.C);
}

void I8080_JM(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, cpu.Status.S);
}

void I8080_JP(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, !cpu.Status.S);
}

void I8080_JZ(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, cpu.Status.Z);
}

void I8080_JNZ(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, !cpu.Status.Z);
}

void I8080_JPE(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, cpu.Status.P);
}

void I8080_JPO(Memory &memory, I8080 &cpu) {
    GenericJump_Conditional(memory, cpu, !cpu.Status.P);
}
