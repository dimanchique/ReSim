#include "Operations/CPU6502_INC_Ops.h"
#include "CPU6502.h"

void CPU6502_INC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.FetchByte(memory);
    GenericINC(memory, cpu, address);
}

void CPU6502_INC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE address = cpu.GetZeroPageAddress(memory, cpu.X);
    GenericINC(memory, cpu, address);
}

void CPU6502_INC_ABS(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.FetchWord(memory);
    GenericINC(memory, cpu, address);
}

void CPU6502_INC_ABSX(Memory &memory, CPU6502 &cpu) {
    const WORD address = cpu.GetAbsAddress(memory, cpu.X);
    GenericINC(memory, cpu, address);
    cpu.cycles++; // extra cycle required
}

void CPU6502_INX_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.X++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INY_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.Y++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
