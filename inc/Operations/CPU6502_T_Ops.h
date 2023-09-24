#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void ExecuteT(BYTE sourceRegister, BYTE &destinationRegister, U32 &cycles, CPU6502 &cpu, bool ShouldCheckStatus = true);

void CPU6502_TAX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TAY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TYA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TSX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_TXS_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
