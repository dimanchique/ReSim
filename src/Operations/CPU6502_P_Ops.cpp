#include <iostream>
#include "Operations/CPU6502_P_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_PHA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PushByteToStack(Cycles, Memory, CPU.A);
}

void CPU6502_PLA_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.A = CPU.PullByteFromStack(Cycles, Memory);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_PHP_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PushByteToStack(Cycles, Memory, CPU.Status);
}

void CPU6502_PLP_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Status = CPU.PullByteFromStack(Cycles, Memory);
}