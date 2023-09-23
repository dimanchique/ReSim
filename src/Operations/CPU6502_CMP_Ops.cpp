#include "Operations/CPU6502_CM_Ops.h"
#include "Operations/CPU6502_CMP_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CMP_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(cycles, memory, cpu, cpu.A);
}

void CPU6502_CMP_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(cycles, memory, cpu, cpu.A);
}

void CPU6502_CMP_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_CMP_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(cycles, memory, cpu, cpu.A);
}

void CPU6502_CMP_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(cycles, memory, cpu, cpu.A, cpu.X);
}

void CPU6502_CMP_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(cycles, memory, cpu, cpu.A, cpu.Y);
}

void CPU6502_CMP_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory) + cpu.X;
    CPU6502::DoTick(cycles);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, EffectiveAddress);
    const BYTE comparedValue = cpu.A - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, cpu.A >= memoryValue);
}

void CPU6502_CMP_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, EffectiveAddressY);
    const BYTE comparedValue = cpu.A - memoryValue;
    if(CPU6502::isPageCrossed(EffectiveAddressY, EffectiveAddress))
        CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, cpu.A >= memoryValue);
}
