#include "Operations/CPU6502_B_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BCC_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.C, false);
}

void CPU6502_BCS_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.C, true);
}

void CPU6502_BEQ_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.Z, true);
}

void CPU6502_BNE_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.Z, false);
}

void CPU6502_BMI_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.N, true);
}

void CPU6502_BPL_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.N, false);
}

void CPU6502_BVC_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.V, false);
}

void CPU6502_BVS_REL(Memory &memory, CPU6502 &cpu) {
    ExecuteB(memory, cpu, cpu.Status.V, true);
}
