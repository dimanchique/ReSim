#pragma once

struct CPU6502;
struct Memory;

struct CPU6502_LDY_IM{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ZP{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ZPX{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ABS{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDY_ABSX{
    void operator()(Memory &memory, CPU6502 &cpu);
};
