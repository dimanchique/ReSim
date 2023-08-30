#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STA_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(Cycles, memory, cpu, cpu.A);
}

void CPU6502_STA_ZPX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ZP(Cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(Cycles, memory, cpu, cpu.A);
}

void CPU6502_STA_ABSX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(Cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_STA_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ST_ABS(Cycles, memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_STA_INDX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    WORD EffectiveAddress = memory.ReadWord(Cycles, ZeroPageAddress);
    memory.WriteByte(Cycles, cpu.A, EffectiveAddress);
}

void CPU6502_STA_INDY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    WORD EffectiveAddress = memory.ReadWord(Cycles, ZeroPageAddress);
    WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    memory.WriteByte(Cycles, cpu.A, EffectiveAddressY);
}
