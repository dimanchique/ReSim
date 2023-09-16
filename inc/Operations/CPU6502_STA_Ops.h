#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STA_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ZPX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
