#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STX_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.X);
}

void CPU6502_STX_ZPY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_STX_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.X);
}
