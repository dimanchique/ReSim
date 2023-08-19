#include "Operations/CPU6502_LDY_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDY_IM::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE Value = cpu.FetchByte(Cycles, memory);
    cpu.Y = Value;
    cpu.LDYSetStatus();
}

void CPU6502_LDY_ZP::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    cpu.Y = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDYSetStatus();
}

void CPU6502_LDY_ZPX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    cpu.Y = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDYSetStatus();
}

void CPU6502_LDY_ABS::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    cpu.Y = cpu.ReadByte(Cycles, AbsAddress, memory);
    cpu.LDYSetStatus();

}

void CPU6502_LDY_ABSX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressY = AbsAddress + cpu.X;
    cpu.Y = cpu.ReadByte(Cycles, AbsAddressY, memory);
    if(AbsAddressY - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LDYSetStatus();

}
