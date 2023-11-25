#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STY_Ops.h"
#include "CPU6502.h"

void CPU6502_STY_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.Y);
}

void CPU6502_STY_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.Y, cpu.X);
}

void CPU6502_STY_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.Y);
}
