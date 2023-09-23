#include "Operations/CPU6502_SE_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void SE_IMPL(BYTE statusFlag, U32 &cycles, CPU6502 &cpu){
    cpu.Status.SetFlag(statusFlag);
    CPU6502::DoTick(cycles);
}

void CPU6502_SEC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    SE_IMPL(CPU6502_Status_C, cycles, cpu);
}

void CPU6502_SED_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    SE_IMPL(CPU6502_Status_D, cycles, cpu);
}

void CPU6502_SEI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    SE_IMPL(CPU6502_Status_I, cycles, cpu);
}
