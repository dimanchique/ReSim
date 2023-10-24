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
    const BYTE Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteCM(cpu, cpu.A, Data);
}

void CPU6502_CMP_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteCM(cpu, cpu.A, Data);
}
