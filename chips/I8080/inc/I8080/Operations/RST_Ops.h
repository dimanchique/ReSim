#pragma once
#include "I8080/I8080.h"
#include "I8080/I8080_OpCodes.h"

FORCE_INLINE void RST_Generic(Memory &memory, I8080 &cpu, const BYTE resetVector) {
    cpu.PushProgramCounterOntoStack(memory);
    cpu.PC = (WORD)(resetVector << 3);
}

FORCE_INLINE void I8080_RST_0(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b000);
}

FORCE_INLINE void I8080_RST_1(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b001);
}

FORCE_INLINE void I8080_RST_2(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b010);
}

FORCE_INLINE void I8080_RST_3(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b011);
}

FORCE_INLINE void I8080_RST_4(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b100);
}

FORCE_INLINE void I8080_RST_5(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b101);
}

FORCE_INLINE void I8080_RST_6(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b110);
}

FORCE_INLINE void I8080_RST_7(Memory &memory, I8080 &cpu) {
    RST_Generic(memory, cpu, 0b111);
}
