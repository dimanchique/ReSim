#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @instruction Store (generic) – Zero Page
 * @details Stores the contents of the targetRegister into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store.
 */
FORCE_INLINE void MOS6502_ST_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const BYTE targetAddress = cpu.FetchByte(memory);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @instruction Store (generic) – Zero Page (generic)
 * @details Stores the contents of the targetRegister into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store.
 * @param affectingRegister Address offset register.
 */
FORCE_INLINE void MOS6502_ST_ZP(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE targetAddress = cpu.GetZeroPageAddress(memory, affectingRegister);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @instruction Store (generic) – Absolute
 * @details Stores the contents of the targetRegister into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store.
 */
FORCE_INLINE void MOS6502_ST_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister) {
    const WORD targetAddress = cpu.FetchWord(memory);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}

/**
 * @instruction Store (generic) – Absolute (generic)
 * @details Stores the contents of the targetRegister into memory.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store.
 * @param affectingRegister Address offset register.
 */
FORCE_INLINE void MOS6502_ST_ABS(Memory &memory, MOS6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const WORD targetAddress = cpu.GetAbsAddress(memory, affectingRegister, false);
    cpu.WriteByte(memory, targetRegister, targetAddress);
}
