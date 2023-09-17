#include "Operations/CPU6502_SE_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void SE_IMPL(BYTE StatusFlag, U32 &Cycles, CPU6502 &CPU){
    CPU.Status.SetFlag(StatusFlag);
    CPU6502::DoTick(Cycles);
}

void CPU6502_SEC_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    SE_IMPL(CPU6502_Status_C, Cycles, CPU);
}

void CPU6502_SED_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    SE_IMPL(CPU6502_Status_D, Cycles, CPU);
}

void CPU6502_SEI_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    SE_IMPL(CPU6502_Status_I, Cycles, CPU);
}
