#pragma once
#include "CPU6502.h"

inline void ExecuteCL(U32 &cycles, CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.SetStatusFlagValue(statusFlag, false);
    DoTick(cycles);
}

inline void CPU6502_CLC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_C);
}

inline void CPU6502_CLD_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_D);
}

inline void CPU6502_CLI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_I);
}

inline void CPU6502_CLV_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_V);
}
