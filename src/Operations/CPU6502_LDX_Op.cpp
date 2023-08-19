#include "Operations/CPU6502_LDX_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDX_IM::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE Value = cpu.FetchByte(Cycles, memory);
    cpu.X = Value;
    cpu.LDXSetStatus();
}

void CPU6502_LDX_ZP::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    cpu.X = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDXSetStatus();
}

void CPU6502_LDX_ZPY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.Y;
    Cycles--;
    cpu.X = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDXSetStatus();
}

void CPU6502_LDX_ABS::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    cpu.X = cpu.ReadByte(Cycles, AbsAddress, memory);
    cpu.LDXSetStatus();
}

void CPU6502_LDX_ABSY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressY = AbsAddress + cpu.Y;
    cpu.X = cpu.ReadByte(Cycles, AbsAddressY, memory);
    if(AbsAddressY - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LDXSetStatus();
}
