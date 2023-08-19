#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

struct CPU6502_LDY_IM{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ZP{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ZPX{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ABS{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ABSX{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};
