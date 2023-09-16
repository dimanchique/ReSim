#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDA_IM(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZP(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZPX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABS(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDX(U32 &Cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDY(U32 &Cycles, Memory &memory, CPU6502 &cpu);
