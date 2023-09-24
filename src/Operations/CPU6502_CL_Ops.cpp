#include "Operations/CPU6502_CL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteCL(U32 &cycles, CPU6502 &cpu, const BYTE statusFlag) {
    cpu.Status.ResetFlag(statusFlag);
    CPU6502::DoTick(cycles);
}

void CPU6502_CLC_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_C);
}

void CPU6502_CLD_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_D);
}

void CPU6502_CLI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_I);
}

void CPU6502_CLV_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteCL(cycles, cpu, CPU6502_Status_V);
}
