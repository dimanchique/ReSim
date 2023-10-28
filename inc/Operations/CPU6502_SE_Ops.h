#pragma once
#include "CPU6502.h"

inline void ExecuteSE(CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, true);
    cpu.cycles++;
}

inline void CPU6502_SEC_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cpu, CPU6502_Status_C);
}

inline void CPU6502_SED_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cpu, CPU6502_Status_D);
}

inline void CPU6502_SEI_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteSE(cpu, CPU6502_Status_I);
}
