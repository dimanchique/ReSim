#include "Operations/CPU6502_SBC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_SBC_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory, cpu.X);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABSX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory, cpu.X);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABSY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory, cpu.Y);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteSBC(cpu, Data);
}
