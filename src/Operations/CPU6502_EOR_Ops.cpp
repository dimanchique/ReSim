#include "Operations/CPU6502_EOR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_EOR_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory, cpu.X);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(memory, cpu, cpu.X);
}

void CPU6502_EOR_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(memory, cpu, cpu.Y);
}

void CPU6502_EOR_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteEOR(cpu, Data);
}

void CPU6502_EOR_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteEOR(cpu, Data);
}
