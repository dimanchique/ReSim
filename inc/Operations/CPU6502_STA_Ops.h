#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_STA_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_STA_INDY(Memory &memory, CPU6502 &cpu);
