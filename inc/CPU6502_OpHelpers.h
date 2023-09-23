#pragma once
#include <CPU6502_OpCodes.h>

struct Memory;
struct CPU6502;

bool FetchCommand(U32 &cycles, BYTE opcode, Memory& memory, CPU6502& cpu);
