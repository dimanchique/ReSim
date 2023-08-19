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
}

void CPU6502_LDA_ABSX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_ABSY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_INDX::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_INDY::operator()(S32& Cycles, Memory &memory, CPU6502 &cpu) {
}
