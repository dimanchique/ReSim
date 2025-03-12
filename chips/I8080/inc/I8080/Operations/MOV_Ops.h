#pragma once
#include "I8080/I8080.h"

/**
 * @brief Move Data from Register to Register Implementation
 * @details One byte of data is moved from the source register to the register the destination register.
 * The data replaces the contents of the destination register; the source remains unchanged.
 * @param cpu I8080 struct instance.
 * @param destRegister Destination register.
 * @param srcRegister Source register.
 */
FORCE_INLINE void PerformRegToRegMOV(I8080 &cpu, BYTE &destRegister, const BYTE &srcRegister) {
    destRegister = srcRegister;
    cpu.cycles++;
}

/**
 * @brief Move Data from Memory to Register Implementation
 * @details One byte of data is moved from memory location to the register the destination register.
 * The data replaces the contents of the destination register; the source remains unchanged.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param destRegister Destination register.
 */
FORCE_INLINE void PerformMemToRegMOV(I8080 &cpu, BYTE &destRegister) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    destRegister = cpu.ReadByte(memoryAddress);
}

/**
 * @brief Move Data from Register To Memory Implementation
 * @details One byte of data is moved from source register to the memory location formed using HL register.
 * The data replaces the contents of the destination register; the source remains unchanged.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @param srcRegister Source register.
 */
FORCE_INLINE void PerformRegToMemMOV(I8080 &cpu, const BYTE &srcRegister) {
    const WORD memoryAddress = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
    cpu.WriteByte(srcRegister, memoryAddress);
}
