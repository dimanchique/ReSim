#pragma once
#include "I8080.h"

/**
 * @brief Load H And L Direct
 * @details The byte at the memory address (immediate value) replaces the contents of the H and L registers.
 * @param cpu I8080 struct instance.
 */
void I8080_LHLD(I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord();
    const WORD memoryValue = cpu.ReadWord(memoryAddress);
    cpu.L = memoryValue & 0xFF;
    cpu.H = (memoryValue >> 8) & 0xFF;
}
