#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister);
void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister);
void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister);
void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister);
