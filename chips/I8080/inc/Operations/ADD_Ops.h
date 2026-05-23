#pragma once
#include "I8080.h"

/**
 * @brief Add Register or Memory To Accumulator Implementation
 * @details The specified byte is added to the contents of the Accumulator using two's complement arithmetic.
 * @short A,C,Z,S,P,AC = A+(Register or Memory)
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to add to Accumulator.
 */
FORCE_INLINE void PerformAdd(I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A + targetRegister;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlag(initialAccumulator, targetRegister);
}

/**
 * @brief Add Accumulator To Accumulator (special case)
 * @details The content of the Accumulator is added to the contents of the Accumulator using two's complement arithmetic.
 * @short A,C,Z,S,P,AC = A+A
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_A(I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD addResult = cpu.A << 1;
    cpu.Status.C = addResult > 0xFF;
    cpu.A = addResult;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlag(initialAccumulator, initialAccumulator);
}

/**
 * @brief Add B To Accumulator
 * @short A,C,Z,S,P,AC = A+B
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_B(I8080 &cpu) {
    PerformAdd(cpu, cpu.B);
}

/**
 * @brief Add C To Accumulator
 * @short A,C,Z,S,P,AC = A+C
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_C(I8080 &cpu) {
    PerformAdd(cpu, cpu.C);
}

/**
 * @brief Add D To Accumulator
 * @short A,C,Z,S,P,AC = A+D
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_D(I8080 &cpu) {
    PerformAdd(cpu, cpu.D);
}

/**
 * @brief Add E To Accumulator
 * @short A,C,Z,S,P,AC = A+E
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_E(I8080 &cpu) {
    PerformAdd(cpu, cpu.E);
}

/**
 * @brief Add H To Accumulator
 * @short A,C,Z,S,P,AC = A+H
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_H(I8080 &cpu) {
    PerformAdd(cpu, cpu.H);
}

/**
 * @brief Add L To Accumulator
 * @short A,C,Z,S,P,AC = A+L
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_L(I8080 &cpu) {
    PerformAdd(cpu, cpu.L);
}

/**
 * @brief Add Memory To Accumulator
 * @short A,C,Z,S,P,AC = A+Memory (immediate value)
 * @param cpu I8080 struct instance.
 */
void I8080_ADD_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    const BYTE addValue = cpu.ReadByte(memoryAddress);
    PerformAdd(cpu, addValue);
}

/**
 * @brief Add Immediate To Accumulator
 * @short A,C,Z,S,P,AC = A+Memory (immediate value)
 * @param cpu I8080 struct instance.
 */
void I8080_ADI(I8080 &cpu) {
    const BYTE addValue = cpu.FetchByte();
    PerformAdd(cpu, addValue);
}
