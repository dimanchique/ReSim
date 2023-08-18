#pragma once

struct CPU6502;
struct Memory;

struct CPU6502_LDX_IM{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ZP{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ZPX{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ABS{
    void operator()(Memory &memory, CPU6502 &cpu);
};

struct CPU6502_LDX_ABSY{
    void operator()(Memory &memory, CPU6502 &cpu);
};
