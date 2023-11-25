#include "Operations/CPU6502_ORA_Ops.h"
#include "CPU6502.h"

void CPU6502_ORA_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericORA(cpu, value);
}

void CPU6502_ORA_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericORA(cpu, value);
}

void CPU6502_ORA_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericORA(cpu, value);
}

void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericORA(cpu, value);
}

void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericORA(cpu, value);
}

void CPU6502_ORA_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(memory, cpu, cpu.X);
}

void CPU6502_ORA_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(memory, cpu, cpu.Y);
}

void CPU6502_ORA_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericORA(cpu, value);
}

void CPU6502_ORA_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericORA(cpu, value);
}
