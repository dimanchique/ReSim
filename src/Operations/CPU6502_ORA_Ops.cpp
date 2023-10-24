#include "Operations/CPU6502_ORA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ORA_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(cycles, memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory, cpu.X);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory, affectingRegister);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_ORA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_ORA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteORA(cpu, Data);
}

void CPU6502_ORA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteORA(cpu, Data);
}
