#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STX_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.X);
}

void CPU6502_STX_ZPY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_STX_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(cycles, memory, cpu, cpu.X);
}
