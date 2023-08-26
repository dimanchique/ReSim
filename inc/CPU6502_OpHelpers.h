#pragma once
#include <CPU6502_OpCodes.h>

struct Memory;
struct CPU6502;

BYTE FetchCommand(S32& Cycles, BYTE OpCode, Memory& Memory, CPU6502& CPU);
