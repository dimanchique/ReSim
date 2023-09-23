#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_CMP_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_CMP_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
