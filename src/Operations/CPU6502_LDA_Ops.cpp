#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(memory, cpu, cpu.A);
}

void CPU6502_LDA_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.A);
}

void CPU6502_LDA_ZPX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A);
}

void CPU6502_LDA_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_LDA_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    GenericLD(cpu, cpu.A, Data);
}

void CPU6502_LDA_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    GenericLD(cpu, cpu.A, Data);
}
