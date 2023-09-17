#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STA_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_STA_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_STA_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ABS(Cycles, Memory, CPU, CPU.A);
}

void CPU6502_STA_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ABS(Cycles, Memory, CPU, CPU.A, CPU.X);
}

void CPU6502_STA_ABSY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ABS(Cycles, Memory, CPU, CPU.A, CPU.Y);
}

void CPU6502_STA_INDX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += CPU.X;
    CPU6502::DoTick(Cycles);                                    //Extra cycle needed in STA
    WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    CPU.WriteByte(Cycles, Memory, CPU.A, EffectiveAddress);
}

void CPU6502_STA_INDY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + CPU.Y;
    CPU6502::DoTick(Cycles);                                    //Extra cycle needed in STA
    CPU.WriteByte(Cycles, Memory, CPU.A, EffectiveAddressY);
}
