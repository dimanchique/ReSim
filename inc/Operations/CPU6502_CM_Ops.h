#pragma once
#include "CPU6502.h"

inline void ExecuteCM(CPU6502 &cpu, const BYTE& targetRegister, const BYTE memoryValue) {
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatusByValue(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

inline void CPU6502_CM_IM(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteCM(cpu, targetRegister, Data);
}

inline void CPU6502_CM_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteCM(cpu, targetRegister, Data);
}

inline void CPU6502_CM_ZP(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetZeroPageValue(memory, affectingRegister);
    ExecuteCM(cpu, targetRegister, Data);
}

inline void CPU6502_CM_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteCM(cpu, targetRegister, Data);
}

inline void CPU6502_CM_ABS(Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteCM(cpu, targetRegister, Data);
}
