#pragma once
#include <CPU6502_OpCodes.h>

struct Memory;
struct CPU6502;

void FetchCommand(S32& cycles, BYTE opcode, Memory& memory, CPU6502& cpu);
void DumpStack(S32& cycles, Memory& memory, CPU6502& cpu);
