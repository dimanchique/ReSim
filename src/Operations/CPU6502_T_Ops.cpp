#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.A, cpu.X, cycles, cpu);
}

void CPU6502_TXA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.X, cpu.A, cycles, cpu);
}

void CPU6502_TAY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.A, cpu.Y, cycles, cpu);
}

void CPU6502_TYA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.Y, cpu.A, cycles, cpu);
}

void CPU6502_TSX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT(cpu.SP, cpu.X, cycles, cpu);
}

void CPU6502_TXS_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteT_NoCheck(cpu.X, cpu.SP, cycles, cpu);
}
