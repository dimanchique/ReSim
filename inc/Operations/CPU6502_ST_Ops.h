#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister);
void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister);
void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister);
void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister);
