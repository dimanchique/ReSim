#include "Operations/CPU6502_B_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteB(U32 &cycles, Memory &memory, CPU6502 &cpu, const BYTE targetFlag, const bool expectedValue) {
    const SBYTE Offset = cpu.FetchByte(cycles, memory);
    if (targetFlag == expectedValue) {
        CPU6502::DoTick(cycles);
        if (CPU6502::IsPageCrossed(cpu.PC, cpu.PC + Offset))
            CPU6502::DoTick(cycles);
        cpu.PC += Offset;
    }
}

void CPU6502_BCC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.C, false);
}

void CPU6502_BCS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.C, true);
}

void CPU6502_BEQ_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.Z, true);
}

void CPU6502_BNE_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.Z, false);
}

void CPU6502_BMI_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.N, true);
}

void CPU6502_BPL_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.N, false);
}

void CPU6502_BVC_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.V, false);
}

void CPU6502_BVS_REL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    ExecuteB(cycles, memory, cpu, cpu.Status.V, true);
}
