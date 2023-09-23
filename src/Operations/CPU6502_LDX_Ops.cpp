#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDX_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZPY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_LDX_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.X, cpu.Y);
}
