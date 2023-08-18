#include "Operations/CPU6502_LDA_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDA_IM::operator()(Memory &memory, CPU6502 &cpu) {
    std::printf("LDA_IM\n");
    BYTE Value = cpu.FetchByte(memory);
    cpu.A = Value;
    cpu.LDASetStatus();
    std::printf("Value 0x%x loaded to A\n", Value);
}

void CPU6502_LDA_ZP::operator()(Memory &memory, CPU6502 &cpu) {
    std::printf("LDA_ZP\n");
    BYTE ZeroPageAddress = cpu.FetchByte(memory);
    cpu.A = cpu.ReadByte(ZeroPageAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_ZPX::operator()(Memory &memory, CPU6502 &cpu) {
    std::printf("LDA_ZPX\n");
    BYTE ZeroPageAddress = cpu.FetchByte(memory);
    ZeroPageAddress += cpu.X;
    cpu.A = cpu.ReadByte(ZeroPageAddress, memory);
    cpu.LDASetStatus();
}

void CPU6502_LDA_ABS::operator()(Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_ABSX::operator()(Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_ABSY::operator()(Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_INDX::operator()(Memory &memory, CPU6502 &cpu) {
}

void CPU6502_LDA_INDY::operator()(Memory &memory, CPU6502 &cpu) {
}
