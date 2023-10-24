#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(cycles, memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_LDA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteLD(cpu, cpu.A, Data);
}

void CPU6502_LDA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteLD(cpu, cpu.A, Data);
}
