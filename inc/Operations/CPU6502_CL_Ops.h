#pragma once
#include "CPU6502.h"

inline void ExecuteCL(CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, false);
    cpu.cycles++;
}

inline void CPU6502_CLC_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cpu, CPU6502_Status_C);
}

inline void CPU6502_CLD_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cpu, CPU6502_Status_D);
}

inline void CPU6502_CLI_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cpu, CPU6502_Status_I);
}

inline void CPU6502_CLV_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cpu, CPU6502_Status_V);
}
