#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

struct CPU6502_LDX_IM{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ZP{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ZPY{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ABS{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ABSY{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};
