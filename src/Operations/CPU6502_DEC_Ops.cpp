#include "Operations/CPU6502_DEC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_DEC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericDEC(memory, cpu, address);
}

void CPU6502_DEC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericDEC(memory, cpu, address);
}

void CPU6502_DEC_ABS(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericDEC(memory, cpu, address);
}

void CPU6502_DEC_ABSX(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericDEC(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}

void CPU6502_DEX_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.X--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEY_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.Y--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
