#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STX_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(Cycles, memory, cpu, cpu.X);
}

void CPU6502_STX_ZPY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(Cycles, memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_STX_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(Cycles, memory, cpu, cpu.X);
}
