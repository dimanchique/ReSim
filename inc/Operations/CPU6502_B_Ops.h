#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

void CPU6502_B_REL(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE TargetFlag, bool ExpectedValue);

void CPU6502_BCC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BCS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BEQ_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BNE_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BMI_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BPL_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BVC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
void CPU6502_BVS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu);
