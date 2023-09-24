#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void ExecuteLD(CPU6502 &cpu, BYTE &targetRegister, const BYTE &value);

void CPU6502_LD_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister);
void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister);
void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister);
void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister);
void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister);
