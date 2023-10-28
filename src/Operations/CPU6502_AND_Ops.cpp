#include "Operations/CPU6502_AND_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_AND_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory, cpu.X);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(memory, cpu, cpu.X);
}

void CPU6502_AND_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(memory, cpu, cpu.Y);
}

void CPU6502_AND_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteAND(cpu, Data);
}
