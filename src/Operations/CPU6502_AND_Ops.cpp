#include "Operations/CPU6502_AND_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_AND_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(cycles, memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory, cpu.X);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory, affectingRegister);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_AND_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_AND_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteAND(cpu, Data);
}

void CPU6502_AND_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteAND(cpu, Data);
}
