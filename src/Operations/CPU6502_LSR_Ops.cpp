#include "Operations/CPU6502_LSR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LSR_ACC(Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_LSR_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericLSR(memory, cpu, address);
}

void CPU6502_LSR_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericLSR(memory, cpu, address);
}

void CPU6502_LSR_ABS(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericLSR(memory, cpu, address);
}

void CPU6502_LSR_ABSX(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericLSR(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}
