#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_SBC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_SBC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu);
