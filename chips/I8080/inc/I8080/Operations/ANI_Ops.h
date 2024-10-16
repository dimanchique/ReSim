#pragma once
#include "I8080/I8080.h"

void I8080_ANI(Memory &memory, I8080 &cpu) {
    const BYTE memoryValue = cpu.FetchByte(memory);
    cpu.A &= memoryValue;
    cpu.Status.UpdateStatusByValue(cpu.A, I8080_Status_S | I8080_Status_P | I8080_Status_Z);
}
