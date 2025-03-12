#pragma once
#include "I8080/I8080.h"

/**
 * @brief Subtract Register or Memory From Accumulator With Borrow Implementation
 * @details The Carry bit is internally added to the contents of the specified byte.
 * This value is then subtracted from the accumulator using two's complement arithmetic.
 * @short A,C,Z,S,P,AC = A+(-(Carry+(Register or Memory)))
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to subtract from Accumulator.
 */
FORCE_INLINE void PerformSBB(I8080 &cpu, const BYTE &targetRegister) {
    const BYTE initialAccumulator = cpu.A;
    const BYTE twosComplement = ~(targetRegister + cpu.Status.C) + 1;
    const WORD subResult = (WORD)cpu.A + twosComplement;
    const bool carryOut = ((subResult & 0x0100) != 0);
    if (carryOut)
        cpu.Status.C = 0;
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_P);
    cpu.Status.S = initialAccumulator < targetRegister;
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, twosComplement);
}

/**
 * @brief Subtract Accumulator From Accumulator With Borrow (special case)
 * @details The two's compliment content of the Accumulator plus the content of the Carry bit is subtracted from the contents of the Accumulator.
 * @short A,C,Z,S,P,AC = A+(-(Carry+A))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_A(I8080 &cpu) {
    const BYTE initialAccumulator = cpu.A;
    const WORD subResult = (WORD)cpu.A + (~cpu.A + 1 + cpu.Status.C);
    cpu.Status.C = ((subResult & 0x0100) != 0);
    cpu.A = subResult & 0xFF;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_Z | I8080_Status_S | I8080_Status_P);
    cpu.Status.SetAuxiliaryCarryFlagOfAdd(initialAccumulator, initialAccumulator);
}

/**
 * @brief Subtract B From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+B))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_B(I8080 &cpu) {
    PerformSBB(cpu, cpu.B);
}

/**
 * @brief Subtract C From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+C))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_C(I8080 &cpu) {
    PerformSBB(cpu, cpu.C);
}

/**
 * @brief Subtract D From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+D))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_D(I8080 &cpu) {
    PerformSBB(cpu, cpu.D);
}

/**
 * @brief Subtract E From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+E))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_E(I8080 &cpu) {
    PerformSBB(cpu, cpu.E);
}

/**
 * @brief Subtract H From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+H))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_H(I8080 &cpu) {
    PerformSBB(cpu, cpu.H);
}

/**
 * @brief Subtract L From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+L))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_L(I8080 &cpu) {
    PerformSBB(cpu, cpu.L);
}

/**
 * @brief Subtract Memory From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+Memory))
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBB_M(I8080 &cpu) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    const BYTE subValue = cpu.ReadByte(memoryAddress);
    PerformSBB(cpu, subValue);
}

/**
 * @brief Subtract Immediate From Accumulator With Borrow
 * @short A,C,Z,S,P,AC = A+(-(Carry+Memory)) (immediate value)
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 */
void I8080_SBI(I8080 &cpu) {
    const BYTE subValue = cpu.FetchByte();
    PerformSBB(cpu, subValue);
}
