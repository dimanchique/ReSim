#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CMP_IM(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ZP(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ZPX(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABS(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABSX(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABSY(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_INDX(Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_INDY(Memory &memory, CPU6502 &cpu);
