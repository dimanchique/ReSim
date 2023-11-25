#include "Operations/CPU6502_ASL_Ops.h"
#include "CPU6502.h"

void CPU6502_ASL_ACC(Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ASL_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericASL(memory, cpu, address);
}

void CPU6502_ASL_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericASL(memory, cpu, address);
}

void CPU6502_ASL_ABS(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericASL(memory, cpu, address);
}

void CPU6502_ASL_ABSX(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericASL(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}
