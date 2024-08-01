#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void I8080_CALL(Memory &memory, I8080 &cpu) {
    const WORD newPC = cpu.FetchWord(memory);
    cpu.PushProgramCounterOntoStack(memory);
    cpu.PC = newPC;
}

FORCE_INLINE void GenericCall_Conditional(Memory &memory, I8080 &cpu, const bool &conditionFlag) {
    const WORD newPC = cpu.FetchWord(memory);
    if (conditionFlag) {
        cpu.PushProgramCounterOntoStack(memory);
        cpu.PC = newPC;
    }
    cpu.cycles++;
}

FORCE_INLINE void I8080_CC(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, cpu.Status.C);
}

FORCE_INLINE void I8080_CNC(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, !cpu.Status.C);
}

FORCE_INLINE void I8080_CM(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, cpu.Status.S);
}

FORCE_INLINE void I8080_CP(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, !cpu.Status.S);
}

FORCE_INLINE void I8080_CZ(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, cpu.Status.Z);
}

FORCE_INLINE void I8080_CNZ(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, !cpu.Status.Z);
}

FORCE_INLINE void I8080_CPE(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, cpu.Status.P);
}

FORCE_INLINE void I8080_CPO(Memory &memory, I8080 &cpu) {
    GenericCall_Conditional(memory, cpu, !cpu.Status.P);
}
