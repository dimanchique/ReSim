#pragma once
#include <CPU6502_OpCodes.h>

struct Memory;
struct CPU6502;

bool FetchCommand(U32 &Cycles, BYTE opcode, Memory& memory, CPU6502& cpu);
void DumpStack(U32 &Cycles, Memory& memory, CPU6502& cpu);
