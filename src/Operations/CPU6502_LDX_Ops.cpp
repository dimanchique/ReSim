#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDX_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(memory, cpu, cpu.X);
}

void CPU6502_LDX_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.X);
}

void CPU6502_LDX_ZPY(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.X, cpu.Y);
}

void CPU6502_LDX_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.X);
}

void CPU6502_LDX_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.X, cpu.Y);
}
