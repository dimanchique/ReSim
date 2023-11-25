#include "Operations/CPU6502_ADC_Ops.h"
#include "CPU6502.h"

void CPU6502_ADC_IM(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.FetchByte(memory);
    GenericADC(cpu, value);
}

void CPU6502_ADC_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericADC(cpu, value);
}

void CPU6502_ADC_ZPX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory, cpu.X);
    GenericADC(cpu, value);
}

void CPU6502_ADC_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericADC(cpu, value);
}

void CPU6502_ADC_ABS(Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const BYTE value = cpu.GetAbsValue(memory, affectingRegister);
    GenericADC(cpu, value);
}

void CPU6502_ADC_ABSX(Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(memory, cpu, cpu.X);
}

void CPU6502_ADC_ABSY(Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(memory, cpu, cpu.Y);
}

void CPU6502_ADC_INDX(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndXAddressValue(memory);
    GenericADC(cpu, value);
}

void CPU6502_ADC_INDY(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetIndYAddressValue(memory);
    GenericADC(cpu, value);
}
