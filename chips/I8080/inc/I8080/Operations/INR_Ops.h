#pragma once
#include "I8080/I8080.h"

/**
 * @brief Increment Register Implementation
 * @details The specified register is incremented by one.
 * @short Register,S,P,Z = Register+1
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to increment.
 */
FORCE_INLINE void PerformINR(I8080 &cpu, BYTE &targetRegister) {
    const BYTE targetCopy = targetRegister;
    targetRegister += 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(targetRegister, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(targetCopy, 0x01);
}

/**
 * @brief Increment Accumulator
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_A(I8080 &cpu) {
    PerformINR(cpu, cpu.A);
}

/**
 * @brief Increment B
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_B(I8080 &cpu) {
    PerformINR(cpu, cpu.B);
}

/**
 * @brief Increment C
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_C(I8080 &cpu) {
    PerformINR(cpu, cpu.C);
}

/**
 * @brief Increment D
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_D(I8080 &cpu) {
    PerformINR(cpu, cpu.D);
}

/**
 * @brief Increment E
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_E(I8080 &cpu) {
    PerformINR(cpu, cpu.E);
}

/**
 * @brief Increment H
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_H(I8080 &cpu) {
    PerformINR(cpu, cpu.H);
}

/**
 * @brief Increment L
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_L(I8080 &cpu) {
    PerformINR(cpu, cpu.L);
}

/**
 * @brief Increment Memory value
 * @details The specified memory byte is incremented by one.
 * @short Mem,S,P,Z = Memory+1
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_INR_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    BYTE memoryValue = cpu.ReadByte(memoryAddress);
    const BYTE memoryCopy = memoryValue;
    memoryValue += 1;
    cpu.WriteByte(memoryValue, memoryAddress);
    cpu.Status.UpdateStatusByValue(memoryValue, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(memoryCopy, 0x01);
}
