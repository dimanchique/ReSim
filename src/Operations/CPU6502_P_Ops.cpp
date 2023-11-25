#include "Operations/CPU6502_P_Ops.h"
#include "CPU6502.h"

void CPU6502_PHA_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PushByteToStack(memory, cpu.A);
}

void CPU6502_PLA_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.A = cpu.PopByteFromStack(memory);
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_PHP_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PushStatusToStack(memory);
}

void CPU6502_PLP_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.PopStatusFromStack(memory);
}
