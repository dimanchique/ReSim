#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.X = cpu.A;
    cpu.LoadRegisterSetStatus(cpu.X);
    Cycles--;
}

void CPU6502_TXA_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.A = cpu.X;
    cpu.LoadRegisterSetStatus(cpu.A);
    Cycles--;
}

void CPU6502_TAY_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.Y = cpu.A;
    cpu.LoadRegisterSetStatus(cpu.Y);
    Cycles--;
}

void CPU6502_TYA_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.A = cpu.Y;
    cpu.LoadRegisterSetStatus(cpu.A);
    Cycles--;
}

void CPU6502_TSX_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.X = cpu.SP;
    cpu.LoadRegisterSetStatus(cpu.X);
    Cycles--;
}

void CPU6502_TXS_IMPL(S32& Cycles, Memory &memory, CPU6502 &cpu){
    cpu.SP = cpu.X;
    Cycles--;
}
