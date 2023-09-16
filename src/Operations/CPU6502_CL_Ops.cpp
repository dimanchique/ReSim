#include "Operations/CPU6502_CL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CL_IMPL(BYTE StatusFlag, U32 &Cycles, CPU6502 &CPU){
    CPU.Status.ClearFlag(StatusFlag);
    Cycles++;
}

void CPU6502_CLC_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CL_IMPL(CPU6502_Status_C, Cycles, CPU);
}

void CPU6502_CLD_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CL_IMPL(CPU6502_Status_D, Cycles, CPU);
}

void CPU6502_CLI_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CL_IMPL(CPU6502_Status_I, Cycles, CPU);
}

void CPU6502_CLV_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CL_IMPL(CPU6502_Status_V, Cycles, CPU);
}
