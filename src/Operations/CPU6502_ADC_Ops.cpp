#include "Operations/CPU6502_ADC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ADC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(cycles, memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory, cpu.X);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory, affectingRegister);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_ADC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_ADC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteADC(cpu, Data);
}
