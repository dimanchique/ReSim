#pragma once

struct CPU6502;
struct Memory;

struct CPU6502_LDA_IM{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ZP{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ZPX{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABS{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABSX{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_ABSY{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_INDX{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDA_INDY{
    void operator()(Memory &memory, CPU6502 &cpu);
};