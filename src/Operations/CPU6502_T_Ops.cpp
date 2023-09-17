#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_T_IMPL(BYTE SourceRegister, BYTE &DestinationRegister, U32 &Cycles, CPU6502 &CPU, bool ShouldCheckStatus = true) {
    DestinationRegister = SourceRegister;
    if(ShouldCheckStatus)
        CPU.SetStatusValue(DestinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(Cycles);
}

void CPU6502_TAX_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.A, CPU.X, Cycles, CPU);
}

void CPU6502_TXA_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.X, CPU.A, Cycles, CPU);
}

void CPU6502_TAY_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.A, CPU.Y, Cycles, CPU);
}

void CPU6502_TYA_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.Y, CPU.A, Cycles, CPU);
}

void CPU6502_TSX_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.SP, CPU.X, Cycles, CPU);
}

void CPU6502_TXS_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU6502_T_IMPL(CPU.X, CPU.SP, Cycles, CPU, false);
}
