#pragma once
#include "I8080/I8080.h"

FORCE_INLINE void GenericLXI(Memory &memory, I8080 &cpu, WORD& targetRegisterPtr) {
    const WORD immediateValue = cpu.FetchWord(memory);
    targetRegisterPtr = immediateValue;
}

void I8080_LXI_B(Memory &memory, I8080 &cpu) {
    GenericLXI(memory, cpu, cpu.BC);
}

void I8080_LXI_D(Memory &memory, I8080 &cpu) {
    GenericLXI(memory, cpu, cpu.DE);
}

void I8080_LXI_H(Memory &memory, I8080 &cpu) {
    GenericLXI(memory, cpu, cpu.HL);
}

void I8080_LXI_SP(Memory &memory, I8080 &cpu) {
    GenericLXI(memory, cpu, cpu.SP);
}
