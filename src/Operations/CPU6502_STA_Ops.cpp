#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.A);
}

void CPU6502_STA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(cycles, memory, cpu, cpu.A);
}

void CPU6502_STA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(cycles, memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_STA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += cpu.X;
    CPU6502::DoTick(cycles);                                    //Extra cycle needed in STA
    WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    CPU6502::WriteByte(cycles, memory, cpu.A, EffectiveAddress);
}

void CPU6502_STA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    CPU6502::DoTick(cycles);                                    //Extra cycle needed in STA
    CPU6502::WriteByte(cycles, memory, cpu.A, EffectiveAddressY);
}
