#include "Operations/CPU6502_AND_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_AND_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericAND(cpu, value);
}

void CPU6502_AND_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericAND(cpu, value);
}

void CPU6502_AND_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericAND(cpu, value);
}

void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericAND(cpu, value);
}

void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericAND(cpu, value);
}

void CPU6502_AND_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(memory, cpu, cpu.X);
}

void CPU6502_AND_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(memory, cpu, cpu.Y);
}

void CPU6502_AND_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericAND(cpu, value);
}

void CPU6502_AND_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericAND(cpu, value);
}
