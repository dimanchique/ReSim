#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_AND_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_AND_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
