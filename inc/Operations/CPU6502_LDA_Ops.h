#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDA_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDY(Memory &memory, CPU6502 &cpu);
