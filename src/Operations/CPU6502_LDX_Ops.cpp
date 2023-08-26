#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDX_IM(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ZPY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.Y;
    Cycles--;
    cpu.X = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LoadRegisterSetStatus(cpu.X);
}

void CPU6502_LDX_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.X);
}

void CPU6502_LDX_ABSY(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressY = AbsAddress + cpu.Y;
    cpu.X = cpu.ReadByte(Cycles, AbsAddressY, memory);
    if(AbsAddressY - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LoadRegisterSetStatus(cpu.X);
}
