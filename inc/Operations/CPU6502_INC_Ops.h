#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void ExecuteINC(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE memoryValue, WORD address);

void CPU6502_INC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_INY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu);
