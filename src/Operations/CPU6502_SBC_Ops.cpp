#include "Operations/CPU6502_SBC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_SBC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(cycles, memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory, cpu.X);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory, cpu.X);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory, cpu.Y);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data);
}

void CPU6502_SBC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data);
}
