#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LD_IM(U32 &Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister);
void CPU6502_LD_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister);
void CPU6502_LD_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister);
void CPU6502_LD_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister);
void CPU6502_LD_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister);
