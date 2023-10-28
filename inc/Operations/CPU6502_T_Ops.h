#pragma once
#include "CPU6502.h"

inline void ExecuteT(const BYTE sourceRegister, BYTE &destinationRegister, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    cpu.Status.UpdateStatusByValue(destinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.cycles++;
}

inline void ExecuteT_NoCheck(const BYTE sourceRegister, BYTE &destinationRegister, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    cpu.cycles++;
}

void CPU6502_TAX_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_TXA_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_TAY_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_TYA_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_TSX_IMPL(Memory &memory, CPU6502 &cpu);
void CPU6502_TXS_IMPL(Memory &memory, CPU6502 &cpu);
