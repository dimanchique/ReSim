#pragma once
#include "CPU6502.h"

inline void CPU6502_ST_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE TargetAddress = cpu.FetchByte(memory);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

inline void CPU6502_ST_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE TargetAddress = cpu.GetZeroPageAddress(memory, affectingRegister);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

inline void CPU6502_ST_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const WORD TargetAddress = cpu.FetchWord(memory);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
}

inline void CPU6502_ST_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const WORD TargetAddress = cpu.GetAbsAddress(memory, affectingRegister);
    cpu.WriteByte(memory, targetRegister, TargetAddress);
    cpu.cycles++; // extra cycle required
}
