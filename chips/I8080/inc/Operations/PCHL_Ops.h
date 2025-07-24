#pragma once
#include "I8080.h"

/**
 * @brief Load Program Counter
 * @details The contents of the H register replace the most significant 8 bits of the program counter, and the contents
 * of the L register replace the least significant 8 bits of the program counter.
 * This causes program execution to continue at the address contained in the Hand L registers.
 * @short PC = HL
 * @param cpu I8080 struct instance.
 */
void I8080_PCHL(I8080 &cpu) {
    cpu.PC = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    ++cpu.cycles;
}
