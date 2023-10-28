#pragma once
#include "CPU6502.h"

inline void ExecuteLD(CPU6502 &cpu, BYTE &targetRegister, const BYTE &value) {
    targetRegister = value;
    cpu.Status.UpdateStatusByValue(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

inline void CPU6502_LD_IM(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteLD(cpu, targetRegister, Data);
}

inline void CPU6502_LD_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteLD(cpu, targetRegister, Data);
}

inline void CPU6502_LD_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory, affectingRegister);
    ExecuteLD(cpu, targetRegister, Data);
}

inline void CPU6502_LD_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteLD(cpu, targetRegister, Data);
}

inline void CPU6502_LD_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteLD(cpu, targetRegister, Data);
}
