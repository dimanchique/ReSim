#pragma once
#include "I8080.h"

/**
 * @brief Compare Implementation
 * @details The specified byte is compared to the contents of the Accumulator. The comparison is performed
 * by internally subtracting the contents of Register from the Accumulator (leaving both unchanged)
 * and setting the condition bits according to the result.
 * @short Z,C = A - (Register or Memory)
 * @param cpu I8080 struct instance.
 * @param targetRegister Value to compare Accumulator with
 */
FORCE_INLINE void PerformComparison(I8080 &cpu, const BYTE &targetRegister) {
    const BYTE comparisonResult = cpu.A - targetRegister;
    cpu.Status.C = cpu.A < targetRegister;
    cpu.Status.UpdateStatusByValue(comparisonResult, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
}

/**
 * @brief Compare Accumulator
 * @details Comparison A and A is trivial by definition. All we need to do is to set the condition bits.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_A(I8080 &cpu) {
    cpu.Status.Z = 1;
    cpu.Status.C = 0;
}

/**
 * @brief Compare B
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_B(I8080 &cpu) {
    PerformComparison(cpu, cpu.B);
}

/**
 * @brief Compare C
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_C(I8080 &cpu) {
    PerformComparison(cpu, cpu.C);
}

/**
 * @brief Compare D
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_D(I8080 &cpu) {
    PerformComparison(cpu, cpu.D);
}

/**
 * @brief Compare E
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_E(I8080 &cpu) {
    PerformComparison(cpu, cpu.E);
}

/**
 * @brief Compare H
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_H(I8080 &cpu) {
    PerformComparison(cpu, cpu.H);
}

/**
 * @brief Compare L
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_L(I8080 &cpu) {
    PerformComparison(cpu, cpu.L);
}

/**
 * @brief Compare Memory value
 * @details Memory value address is computing using paired HL as an absolute 16-bit address.
 * @param cpu I8080 struct instance.
 */
void I8080_CMP_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    const BYTE cmpValue = cpu.ReadByte(memoryAddress);
    PerformComparison(cpu, cmpValue);
}

/**
 * @brief Compare Immediate value
 * @param cpu I8080 struct instance.
 */
void I8080_CPI(I8080 &cpu) {
    const BYTE cmpValue = cpu.FetchByte();
    PerformComparison(cpu, cmpValue);
}
