#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.A, cpu.X, cpu);
}

void CPU6502_TXA_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.X, cpu.A, cpu);
}

void CPU6502_TAY_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.A, cpu.Y, cpu);
}

void CPU6502_TYA_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.Y, cpu.A, cpu);
}

void CPU6502_TSX_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.SP, cpu.X, cpu);
}

void CPU6502_TXS_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.SP = cpu.X;
    cpu.cycles++;
}
