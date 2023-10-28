#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDY_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.Y, cpu.X);
}

void CPU6502_LDY_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.Y);
}

void CPU6502_LDY_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.Y, cpu.X);
}
