#pragma once
#include "I8080/I8080.h"

/**
 * @brief Logical OR Implementation
 * @details A logical OR is performed, bit by bit, on the Accumulator contents using the contents of a given byte (register of memory).
 * @short A,S,P,Z = A|(Register or Memory)
 * @param cpu I8080 struct instance.
 * @param value Value to perform OR with.
 */
FORCE_INLINE void PerformORA(I8080 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}

/**
 * @brief Logical OR with register A
 * @details Instruction semantic: A=A|A. Register A stays the same.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_A(I8080 &cpu) {
    PerformORA(cpu, cpu.A);
}

/**
 * @brief Logical OR with register B
 * @details Instruction semantic: A=A|B.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_B(I8080 &cpu) {
    PerformORA(cpu, cpu.B);
}

/**
 * @brief Logical OR with register C
 * @details Instruction semantic: A=A|C.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_C(I8080 &cpu) {
    PerformORA(cpu, cpu.C);
}

/**
 * @brief Logical OR with register D
 * @details Instruction semantic: A=A|D.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_D(I8080 &cpu) {
    PerformORA(cpu, cpu.D);
}

/**
 * @brief Logical OR with register E
 * @details Instruction semantic: A=A|E.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_E(I8080 &cpu) {
    PerformORA(cpu, cpu.E);
}

/**
 * @brief Logical OR with register H
 * @details Instruction semantic: A=A|H.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_H(I8080 &cpu) {
    PerformORA(cpu, cpu.H);
}

/**
 * @brief Logical OR with register L
 * @details Instruction semantic: A=A|L.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_L(I8080 &cpu) {
    PerformORA(cpu, cpu.L);
}

/**
 * @brief Logical OR with memory value
 * @details Instruction semantic: A=A|Memory.
 * Memory value address is computing using paired HL as an absolute 16-bit address.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_ORA_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE value = cpu.ReadByte(memoryAddress);
    PerformORA(cpu, value);
}
