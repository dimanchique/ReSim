#include "Operations/CPU6502_P_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_PHA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.PushByteToStack(cycles, memory, cpu.A);
}

void CPU6502_PLA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.A = cpu.PullByteFromStack(cycles, memory);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_PHP_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.PushByteToStack(cycles, memory, cpu.Status);
}

void CPU6502_PLP_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.Status = cpu.PullByteFromStack(cycles, memory);
}