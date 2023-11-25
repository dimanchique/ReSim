#include "Operations/CPU6502_SBC_Ops.h"
#include "CPU6502.h"

void CPU6502_SBC_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_ABSX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory, cpu.X);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_ABSY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory, cpu.Y);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericSBC(cpu, value);
}

void CPU6502_SBC_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericSBC(cpu, value);
}
