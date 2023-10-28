#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

bool FetchCommand(BYTE opcode, Memory &memory, CPU6502 &cpu);
