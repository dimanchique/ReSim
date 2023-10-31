#pragma once
#include "CPU6502.h"

/**
 * @instruction Load (generic)
 * @details Loads a byte of memory into the targetRegister setting the zero and negative flags as appropriate.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 * @param value Value to load.
 */
inline void GenericLD(CPU6502 &cpu, BYTE &targetRegister, const BYTE &value) {
    targetRegister = value;
    cpu.Status.UpdateStatusByValue(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

/**
 * @instruction Load (generic) – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 */
inline void CPU6502_LD_IM(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.FetchByte(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 */
inline void CPU6502_LD_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Zero Page (generic)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 * @param affectingRegister Address offset register.
 */
inline void CPU6502_LD_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory, affectingRegister);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 */
inline void CPU6502_LD_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetAbsValue(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 * @param targetRegister Register to load to.
 * @param affectingRegister Address offset register.
 */
inline void CPU6502_LD_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    GenericLD(cpu, targetRegister, Data);
}
