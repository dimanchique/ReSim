#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_IM(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_LDA_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_LDA_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_LDA_ABSY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.A, CPU.Y);
}

void CPU6502_LDA_INDX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory) + CPU.X;
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    CPU.A = CPU.ReadByte(Cycles, Memory, EffectiveAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(Cycles);
}

void CPU6502_LDA_INDY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + CPU.Y;
    CPU.A = CPU.ReadByte(Cycles, Memory, EffectiveAddressY);
    if(isPageCrossed(EffectiveAddressY, EffectiveAddress))
        CPU6502::DoTick(Cycles);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}
