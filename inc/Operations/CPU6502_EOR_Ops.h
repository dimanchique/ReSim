#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void ExecuteEOR(CPU6502 &cpu, BYTE value);

void CPU6502_EOR_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_EOR_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
