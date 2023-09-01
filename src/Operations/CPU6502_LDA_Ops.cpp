#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_IM(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ZPX(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_LDA_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ABSX(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_LDA_ABSY(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A, CPU.Y);
}

void CPU6502_LDA_INDX(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += CPU.X;
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    CPU.A = CPU.ReadByte(Cycles, Memory, EffectiveAddress);
    CPU.LoadRegisterSetStatus(CPU.A);
    Cycles--;
}

void CPU6502_LDA_INDY(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + CPU.Y;
    CPU.A = CPU.ReadByte(Cycles, Memory, EffectiveAddressY);
    if(EffectiveAddressY - EffectiveAddress >= 0xFF)
        Cycles--;
    CPU.LoadRegisterSetStatus(CPU.A);
}
