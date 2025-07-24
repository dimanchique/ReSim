#pragma once
#include "I8080.h"

/**
 * @brief Double Add Implementation
 * @details The 16-bit number in the specified register pair is added to the 16-bit number held in the H and L
 * registers using two's complement arithmetic. The result replaces the contents of the Hand L registers.
 * @short HL,C = HL + Register
 * @param cpu I8080 struct instance.
 * @param targetRegister Register to add to HL.
 */
FORCE_INLINE void PerformDAD(I8080 &cpu, const WORD targetRegister) {
    WORD operand = ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L); // we treat paired HL registers as a 16-bit WORD
    U32 result = operand + targetRegister;
    cpu.cycles += 4; // assuming it takes 4 cycles to do 16-bit add

    cpu.L = result & 0xFF;
    ++cpu.cycles;
    cpu.H = (result >> 8) & 0xFF;
    ++cpu.cycles;

    cpu.Status.C = (result & 0XFFFF0000) > 0;
}

/**
 * @brief Double Add BC
 * @short HL,C = HL + BC
 * @param cpu I8080 struct instance.
 */
void I8080_DAD_B(I8080 &cpu) {
    PerformDAD(cpu, ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.B, cpu.C));
}

/**
 * @brief Double Add DE
 * @short HL,C = HL + DE
 * @param cpu I8080 struct instance.
 */
void I8080_DAD_D(I8080 &cpu) {
    PerformDAD(cpu, ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.D, cpu.E));
}

/**
 * @brief Double Add HL
 * @short HL,C = HL + HL
 * @param cpu I8080 struct instance.
 */
void I8080_DAD_H(I8080 &cpu) {
    PerformDAD(cpu, ReSimFunctionLibrary::DataManipulation::putTwoBytesToLIWord(cpu.H, cpu.L));
}

/**
 * @brief Double Add BC
 * @short HL,C = HL + SP
 * @param cpu I8080 struct instance.
 */
void I8080_DAD_SP(I8080 &cpu) {
    PerformDAD(cpu, cpu.SP);
}
