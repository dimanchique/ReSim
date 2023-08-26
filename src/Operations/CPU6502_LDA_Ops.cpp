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
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    cpu.A = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LoadRegisterSetStatus(cpu.A);
}

void CPU6502_LDA_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.A);
}

void CPU6502_LDA_ABSX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressX = AbsAddress + cpu.X;
    cpu.A = cpu.ReadByte(Cycles, AbsAddressX, memory);
    if(AbsAddressX - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LoadRegisterSetStatus(cpu.A);
}

void CPU6502_LDA_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressY = AbsAddress + cpu.Y;
    cpu.A = cpu.ReadByte(Cycles, AbsAddressY, memory);
    if(AbsAddressY - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LoadRegisterSetStatus(cpu.A);
}

void CPU6502_LDA_INDX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    WORD EffectiveAddress = cpu.ReadWord(Cycles, ZeroPageAddress, memory);
    cpu.A = cpu.ReadByte(Cycles, EffectiveAddress, memory);
    cpu.LoadRegisterSetStatus(cpu.A);
}

void CPU6502_LDA_INDY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    WORD EffectiveAddress = cpu.ReadWord(Cycles, ZeroPageAddress, memory);
    WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    cpu.A = cpu.ReadByte(Cycles, EffectiveAddressY, memory);
    if(EffectiveAddressY - EffectiveAddress >= 0xFF)
        Cycles--;
    cpu.LoadRegisterSetStatus(cpu.A);
}
