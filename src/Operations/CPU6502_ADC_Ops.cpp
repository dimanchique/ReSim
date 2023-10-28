#include "Operations/CPU6502_ADC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ADC_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.FetchByte(memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory, cpu.X);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE Data = cpu.GetAbsValue(memory, affectingRegister);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(memory, cpu, cpu.X);
}

void CPU6502_ADC_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(memory, cpu, cpu.Y);
}

void CPU6502_ADC_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndXAddressValue(memory);
    ExecuteADC(cpu, Data);
}

void CPU6502_ADC_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(memory);
    ExecuteADC(cpu, Data);
}
