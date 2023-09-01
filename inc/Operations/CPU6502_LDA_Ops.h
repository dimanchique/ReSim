#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_LDA_IM(S32&   cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZP(S32&   cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ZPX(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABS(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSX(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_ABSY(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDX(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_LDA_INDY(S32& cycles, Memory &memory, CPU6502 &cpu);
