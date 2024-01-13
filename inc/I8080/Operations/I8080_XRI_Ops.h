#pragma once

#include "I8080/I8080.h"

FORCE_INLINE void I8080_XRI(Memory &memory, I8080 &cpu) {
    const BYTE memoryValue = cpu.FetchByte(memory);
    const BYTE targetCopy = cpu.A;
    cpu.A ^= memoryValue;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
    cpu.Status.SetAuxiliaryCarryFlag(targetCopy, cpu.A);
}
