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
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory) + cpu.X;
    CPU6502::DoTick(cycles);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    cpu.A = CPU6502::ReadByte(cycles, memory, EffectiveAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LDA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    cpu.A = CPU6502::ReadByte(cycles, memory, EffectiveAddressY);
    if(CPU6502::isPageCrossed(EffectiveAddressY, EffectiveAddress))
        CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}
