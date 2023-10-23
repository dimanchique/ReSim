#pragma once
#include "CPU6502.h"

inline void ExecuteSE(U32 &cycles, CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetFlag(statusFlag);
    CPU6502::DoTick(cycles);
}

inline void CPU6502_SEC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cycles, cpu, CPU6502_Status_C);
}

inline void CPU6502_SED_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cycles, cpu, CPU6502_Status_D);
}

inline void CPU6502_SEI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cycles, cpu, CPU6502_Status_I);
}
