#pragma once
#include <CPU6502_OpCodes.h>

struct Memory;
struct CPU6502;

unsigned char FetchCommand(BYTE OpCode, Memory& Memory, CPU6502& CPU);
