#pragma once
#include "CPU6502.h"

inline void ExecuteT(const BYTE sourceRegister, BYTE &destinationRegister, U32 &cycles, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    cpu.Status.UpdateStatusByValue(destinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(cycles);
}

inline void ExecuteT_NoCheck(const BYTE sourceRegister, BYTE &destinationRegister, U32 &cycles, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    CPU6502::DoTick(cycles);
}

void CPU6502_TAX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TAY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TYA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TSX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXS_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
