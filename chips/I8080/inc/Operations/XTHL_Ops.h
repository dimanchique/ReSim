#pragma once
#include "I8080.h"

/**
 * @brief Exchange Stack
 * @details Exchange HL register value with a stack top value.
 * @short HL <-> memory[SP]
 * @param cpu I8080 struct instance.
 */
void I8080_XTHL(I8080 &cpu) {
    const WORD stackPointerValue = cpu.ReadWord(cpu.SP);
    const WORD registerValue = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    cpu.WriteWord(registerValue, cpu.SP);

    cpu.L = stackPointerValue & 0xFF;
    ++cpu.cycles;
    cpu.H = (stackPointerValue >> 8) & 0xFF;
    ++cpu.cycles;
}
