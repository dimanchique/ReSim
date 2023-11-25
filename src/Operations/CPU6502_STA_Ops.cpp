#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STA_Ops.h"
#include "CPU6502.h"

void CPU6502_STA_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.A);
}

void CPU6502_STA_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.A);
}

void CPU6502_STA_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_STA_INDX(Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.GetIndXAddress(memory);
    cpu.WriteByte(memory, cpu.A, TargetAddress);
}

void CPU6502_STA_INDY(Memory &memory, CPU6502 &cpu) {
    const WORD TargetAddress = cpu.GetIndYAddress(memory);
    cpu.WriteByte(memory, cpu.A, TargetAddress);
    cpu.cycles++; // extra cycle required
}
