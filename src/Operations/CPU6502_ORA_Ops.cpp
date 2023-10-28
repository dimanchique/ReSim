#include "Operations/CPU6502_ORA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ORA_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory, cpu.X);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(memory, cpu, cpu.X);
}

void CPU6502_ORA_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(memory, cpu, cpu.Y);
}

void CPU6502_ORA_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteORA(cpu, Data);
}
