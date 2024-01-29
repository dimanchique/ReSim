#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Load (generic)
 * @details Loads a byte of memory into the targetRegister setting the zero and negative flags as appropriate.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param value Value to load.
 */
FORCE_INLINE void GenericLD(MOS6502 &cpu, BYTE &targetRegister, const BYTE &value) {
    targetRegister = value;
    cpu.Status.UpdateStatusByValue(targetRegister, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @instruction Load (generic) – Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_IM(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.FetchByte(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Zero Page (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param affectingRegister Address offset register.
 */
FORCE_INLINE void MOS6502_LD_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory, affectingRegister);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 */
FORCE_INLINE void MOS6502_LD_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetAbsValue(memory);
    GenericLD(cpu, targetRegister, Data);
}

/**
 * @instruction Load (generic) – Absolute (generic)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to load to.
 * @param affectingRegister Address offset register.
 */
FORCE_INLINE void MOS6502_LD_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    GenericLD(cpu, targetRegister, Data);
}
