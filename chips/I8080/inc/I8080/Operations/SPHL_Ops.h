#pragma once
#include "I8080/I8080.h"

/**
 * @brief Load SP From H And L
 * @details The 16 bits of data held in the H and L registers replace the contents of the stack pointer SP.
 * The contents of the H and L registers are unchanged.
 * @short SP = HL
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SPHL(I8080 &cpu) {
    cpu.SP = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.cycles++;
}
