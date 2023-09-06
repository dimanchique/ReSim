#include "Operations/CPU6502_SE_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_SEC_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Status.C = 1;
    Cycles -= 2;
}

void CPU6502_SED_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Status.D = 1;
    Cycles -= 2;
}

void CPU6502_SEI_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Status.I = 1;
    Cycles -= 2;
}
