#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_ORA_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_ORA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
