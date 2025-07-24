#pragma once
#include "I8080.h"

/**
 * @brief Decrement Register Implementation
 * @details The specified register is decremented by one.
 * @short Register,S,P,Z = Reg-1
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to decrement.
 */
FORCE_INLINE void PerformDCR(I8080 &cpu, BYTE &targetRegister) {
    const BYTE targetCopy = targetRegister;
    targetRegister = (BYTE)(targetRegister + 0xFF); // +(-1) is better than -1
    ++cpu.cycles;
    cpu.Status.UpdateStatusByValue(targetRegister, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(targetCopy, 0xFF);
}

/**
 * @brief Decrement Accumulator
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_A(I8080 &cpu) {
    PerformDCR(cpu, cpu.A);
}

/**
 * @brief Decrement B
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_B(I8080 &cpu) {
    PerformDCR(cpu, cpu.B);
}

/**
 * @brief Decrement C
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_C(I8080 &cpu) {
    PerformDCR(cpu, cpu.C);
}

/**
 * @brief Decrement D
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_D(I8080 &cpu) {
    PerformDCR(cpu, cpu.D);
}

/**
 * @brief Decrement E
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_E(I8080 &cpu) {
    PerformDCR(cpu, cpu.E);
}

/**
 * @brief Decrement H
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_H(I8080 &cpu) {
    PerformDCR(cpu, cpu.H);
}

/**
 * @brief Decrement L
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_L(I8080 &cpu) {
    PerformDCR(cpu, cpu.L);
}

/**
 * @brief Decrement Memory value
 * @details The specified memory byte is decremented by one.
 * @short Mem,S,P,Z = Memory-1
 * @param cpu I8080 struct instance.
 */
void I8080_DCR_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L);
    BYTE memoryValue = cpu.ReadByte(memoryAddress);
    const BYTE memoryCopy = memoryValue;
    memoryValue = (BYTE)(memoryValue + 0xFF); // +(-1) is better than -1
    cpu.WriteByte(memoryValue, memoryAddress);
    cpu.Status.UpdateStatusByValue(memoryValue, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(memoryCopy, 0xFF);
}
