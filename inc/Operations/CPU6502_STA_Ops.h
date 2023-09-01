#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STA_ZP(S32&   cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ZPX(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABS(S32&  cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSX(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSY(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDX(S32& cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDY(S32& cycles, Memory &memory, CPU6502 &cpu);
