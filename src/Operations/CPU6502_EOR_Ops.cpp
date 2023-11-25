#include "Operations/CPU6502_EOR_Ops.h"
#include "CPU6502.h"

void CPU6502_EOR_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(memory, cpu, cpu.X);
}

void CPU6502_EOR_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(memory, cpu, cpu.Y);
}

void CPU6502_EOR_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericEOR(cpu, value);
}

void CPU6502_EOR_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericEOR(cpu, value);
}
