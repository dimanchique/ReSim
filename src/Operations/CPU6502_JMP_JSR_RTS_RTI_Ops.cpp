#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_JMP_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.PC = cpu.FetchWord(cycles, memory);
}

void CPU6502_JMP_IND(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.FetchWord(cycles, memory);
    cpu.PC = CPU6502::ReadWord(cycles, memory, TargetAddress);
}

void CPU6502_JSR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.FetchWord(cycles, memory);
    cpu.PushProgramCounterToStack(cycles, memory);
    cpu.PC = TargetAddress;
    CPU6502::DoTick(cycles);
}

void CPU6502_RTS_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.PC = cpu.PullAddressFromStack(cycles, memory);
    CPU6502::DoTick(cycles);
}

void CPU6502_RTI_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.PullStatusFromStack(cycles, memory);
    cpu.PC = cpu.PullAddressFromStack(cycles, memory);
    cpu.Status.ResetFlag(CPU6502_Status_B);
    cycles--; // temporary fix extra cycle
}

void CPU6502_BRK_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.PushProgramCounterToStack(cycles, memory);
    cpu.PushStatusToStack(cycles, memory);
    cpu.PC = CPU6502::ReadWord(cycles, memory, 0xFFFE);
    cpu.Status.SetFlag(CPU6502_Status_B);
    cycles--; // temporary fix extra cycle
}
