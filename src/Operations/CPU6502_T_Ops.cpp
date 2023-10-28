#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.A, cpu.X, cpu);
}

void CPU6502_TXA_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.X, cpu.A, cpu);
}

void CPU6502_TAY_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.A, cpu.Y, cpu);
}

void CPU6502_TYA_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.Y, cpu.A, cpu);
}

void CPU6502_TSX_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.SP, cpu.X, cpu);
}

void CPU6502_TXS_IMPL(Memory &memory, CPU6502 &cpu) {
    ExecuteT_NoCheck(cpu.X, cpu.SP, cpu);
}
