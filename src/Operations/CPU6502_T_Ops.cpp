#include "Operations/CPU6502_T_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_T_IMPL(BYTE sourceRegister, BYTE &destinationRegister, U32 &cycles, CPU6502 &cpu, bool ShouldCheckStatus = true) {
    destinationRegister = sourceRegister;
    if(ShouldCheckStatus)
        cpu.Status.UpdateStatus(destinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(cycles);
}

void CPU6502_TAX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.A, cpu.X, cycles, cpu);
}

void CPU6502_TXA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.X, cpu.A, cycles, cpu);
}

void CPU6502_TAY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.A, cpu.Y, cycles, cpu);
}

void CPU6502_TYA_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.Y, cpu.A, cycles, cpu);
}

void CPU6502_TSX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.SP, cpu.X, cycles, cpu);
}

void CPU6502_TXS_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    CPU6502_T_IMPL(cpu.X, cpu.SP, cycles, cpu, false);
}
