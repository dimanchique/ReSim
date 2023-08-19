#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

struct CPU6502_LDA_IM{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ZP{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ZPX{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABS{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABSX{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABSY{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_INDX{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_INDY{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu);
};