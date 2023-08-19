#include "Operations/CPU6502_LDA_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE Value = cpu.FetchByte(Cycles, memory);
    cpu.A = Value;
    cpu.LDASetStatus();
}

void CPU6502_LDA_ZP::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    cpu.A = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_ZPX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    cpu.A = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_ABS::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    cpu.A = cpu.ReadByte(Cycles, AbsAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_ABSX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressX = AbsAddress + cpu.X;
    cpu.A = cpu.ReadByte(Cycles, AbsAddressX, memory);
    if(AbsAddressX - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LDASetStatus();
}

void CPU6502_LDA_ABSY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AbsAddressY = AbsAddress + cpu.Y;
    cpu.A = cpu.ReadByte(Cycles, AbsAddressY, memory);
    if(AbsAddressY - AbsAddress >= 0xFF)
        Cycles--;
    cpu.LDASetStatus();
}

void CPU6502_LDA_INDX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += cpu.X;
    Cycles--;
    WORD EffectiveAddress = cpu.ReadWord(Cycles, ZeroPageAddress, memory);
    cpu.A = cpu.ReadByte(Cycles, EffectiveAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_INDY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    WORD EffectiveAddress = cpu.ReadWord(Cycles, ZeroPageAddress, memory);
    WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    cpu.A = cpu.ReadByte(Cycles, EffectiveAddressY, memory);
    if(EffectiveAddressY - EffectiveAddress >= 0xFF)
        Cycles--;
    cpu.LDASetStatus();
}
