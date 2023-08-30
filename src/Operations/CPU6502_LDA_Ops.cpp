#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(Cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ZPX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ABSX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_LDA_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_LDA_INDX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    WORD EffectiveAddress = memory.ReadWord(Cycles, ZeroPageAddress);
    cpu.A = memory.ReadByte(Cycles, EffectiveAddress);
    cpu.LoadRegisterSetStatus(cpu.A);
}

void CPU6502_LDA_INDY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    WORD EffectiveAddress = memory.ReadWord(Cycles, ZeroPageAddress);
    WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    cpu.A = memory.ReadByte(Cycles, EffectiveAddressY);
    if(EffectiveAddressY - EffectiveAddress >= 0xFF)
        Cycles--;
    cpu.LoadRegisterSetStatus(cpu.A);
}
