#pragma once
#include "I8080/I8080.h"

inline void I8080_XTHL(Memory &memory, I8080 &cpu) {
    const WORD stackPointerValue = cpu.ReadWord(memory, cpu.SP);
    const WORD registerValue = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
    cpu.WriteWord(memory, registerValue, cpu.SP);
    I8080::wordToRegisterSwapped(stackPointerValue, cpu.H, cpu.L);
}
