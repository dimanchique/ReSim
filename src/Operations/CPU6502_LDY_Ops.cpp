#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDY_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.Y, cpu.X);
}

void CPU6502_LDY_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.Y, cpu.X);
}
