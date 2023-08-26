#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDX_IM(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZPY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_LDX_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.X, cpu.Y);
}
