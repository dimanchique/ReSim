#include "Operations/CPU6502_CL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CLC_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.C = 0;
    Cycles -= 2;
}

void CPU6502_CLD_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.D = 0;
    Cycles -= 2;
}

void CPU6502_CLI_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.I = 0;
    Cycles -= 2;
}

void CPU6502_CLV_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.V = 0;
    Cycles -= 2;
}
