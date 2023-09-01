#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X = CPU.A;
    CPU.LoadRegisterSetStatus(CPU.X);
    Cycles--;
}

void CPU6502_TXA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.A = CPU.X;
    CPU.LoadRegisterSetStatus(CPU.A);
    Cycles--;
}

void CPU6502_TAY_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Y = CPU.A;
    CPU.LoadRegisterSetStatus(CPU.Y);
    Cycles--;
}

void CPU6502_TYA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.A = CPU.Y;
    CPU.LoadRegisterSetStatus(CPU.A);
    Cycles--;
}

void CPU6502_TSX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X = CPU.SP;
    CPU.LoadRegisterSetStatus(CPU.X);
    Cycles--;
}

void CPU6502_TXS_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.SP = CPU.X;
    Cycles--;
}
