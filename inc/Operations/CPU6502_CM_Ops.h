#pragma once
#include "CPU6502.h"

/**
 * @instruction Compare (generic)
 * @details This instruction compares the contents of the targetRegister with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 * @param memoryValue Memory value to compare.
 */
inline void GenericCM(CPU6502 &cpu, const BYTE& targetRegister, const BYTE memoryValue) {
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatusByValue(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

/**
 * @instruction Compare (generic) – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 */
inline void CPU6502_CM_IM(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE value = cpu.FetchByte(memory);
    GenericCM(cpu, targetRegister, value);
}

/**
 * @instruction Compare (generic) – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 */
inline void CPU6502_CM_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericCM(cpu, targetRegister, value);
}

/**
 * @instruction Compare (generic) – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 */
inline void CPU6502_CM_ZPX(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericCM(cpu, targetRegister, value);
}

/**
 * @instruction Compare (generic) – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 */
inline void CPU6502_CM_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericCM(cpu, targetRegister, value);
}

/**
 * @instruction Compare (generic) – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to compare.
 * @param affectingRegister Address offset register.
 */
inline void CPU6502_CM_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericCM(cpu, targetRegister, value);
}
