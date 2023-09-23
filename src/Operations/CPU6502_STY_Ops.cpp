#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STY_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.Y);
}

void CPU6502_STY_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.Y, cpu.X);
}

void CPU6502_STY_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(cycles, memory, cpu, cpu.Y);
}
