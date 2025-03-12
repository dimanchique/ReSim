#pragma once
#include "I8080/I8080.h"

/**
 * @brief Store Accumulator Implementation
 * @details Write Accumulator register to a specified memory location.
 * @short M = A
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param memoryAddress Memory location to store Accumulator.
 */
FORCE_INLINE void PerformSTA(I8080 &cpu, const WORD memoryAddress) {
    cpu.WriteByte(cpu.A, memoryAddress);
}

/**
 * @brief Store Accumulator Immediate
 * @details Use immediate value as an address to store Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_STA(I8080 &cpu) {
    const WORD memoryAddress = cpu.FetchWord();
    PerformSTA(cpu, memoryAddress);
}

/**
 * @brief Store Accumulator B
 * @details Use paired BC register value as an address to store Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_STAX_B(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.B, cpu.C);
    PerformSTA(cpu, memoryAddress);
}

/**
 * @brief Store Accumulator D
 * @details Use paired DE register value as an address to store Accumulator.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_STAX_D(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E);
    PerformSTA(cpu, memoryAddress);
}
