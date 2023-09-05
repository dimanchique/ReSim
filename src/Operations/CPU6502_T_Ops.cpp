#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_TAX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X = CPU.A;
    CPU.SetStatusRegisterValue(CPU.X, CPU6502_Status_Z | CPU6502_Status_N);
    Cycles--;
}

void CPU6502_TXA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.A = CPU.X;
    CPU.SetStatusRegisterValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
    Cycles--;
}

void CPU6502_TAY_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Y = CPU.A;
    CPU.SetStatusRegisterValue(CPU.Y, CPU6502_Status_Z | CPU6502_Status_N);
    Cycles--;
}

void CPU6502_TYA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.A = CPU.Y;
    CPU.SetStatusRegisterValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
    Cycles--;
}

void CPU6502_TSX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X = CPU.SP;
    CPU.SetStatusRegisterValue(CPU.X, CPU6502_Status_Z | CPU6502_Status_N);
    Cycles--;
}

void CPU6502_TXS_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.SP = CPU.X;
    Cycles--;
}
