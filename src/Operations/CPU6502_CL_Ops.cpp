#include "Operations/CPU6502_CL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CL_IMPL(BYTE statusFlag, U32 &cycles, CPU6502 &cpu){
    cpu.Status.ResetFlag(statusFlag);
    CPU6502::DoTick(cycles);
}

void CPU6502_CLC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CL_IMPL(CPU6502_Status_C, cycles, cpu);
}

void CPU6502_CLD_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CL_IMPL(CPU6502_Status_D, cycles, cpu);
}

void CPU6502_CLI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CL_IMPL(CPU6502_Status_I, cycles, cpu);
}

void CPU6502_CLV_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CL_IMPL(CPU6502_Status_V, cycles, cpu);
}
