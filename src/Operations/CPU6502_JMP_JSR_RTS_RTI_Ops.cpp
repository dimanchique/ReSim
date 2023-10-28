#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_JMP_ABS(Memory &memory, CPU6502 &cpu) {
    cpu.PC = cpu.FetchWord(memory);
}

void CPU6502_JMP_IND(Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.FetchWord(memory);
    cpu.PC = cpu.ReadWord(memory, TargetAddress);
}

void CPU6502_JSR_ABS(Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.FetchWord(memory);
    cpu.PushProgramCounterToStack(memory);
    cpu.PC = TargetAddress;
    cpu.cycles++;
}

void CPU6502_RTS_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PC = cpu.PopAddressFromStack(memory);
    cpu.cycles++;
}

void CPU6502_RTI_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PopStatusFromStack(memory);
    cpu.PC = cpu.PopAddressFromStack(memory);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_B, false);
    cpu.cycles--; // temporary fix extra cycle
}

void CPU6502_BRK_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PushProgramCounterToStack(memory);
    cpu.PushStatusToStack(memory);
    cpu.PC = cpu.ReadWord(memory, 0xFFFE);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_B, true);
    cpu.cycles--; // temporary fix extra cycle
}
