#pragma once
#include "I8080.h"

/**
 * @brief Store Hand L Direct
 * @details The contents of the HL register are stored at the given memory address (immediate value).
 * @short M = HL
 * @param cpu I8080 struct instance.
 */
void I8080_SHLD(I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord();
    const WORD storeValue = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    cpu.WriteWord(storeValue, memoryAddress);
}
