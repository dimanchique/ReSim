#pragma once

#include "I8086.h"

void I8086_LAHF(BYTE OpCode, I8086 &cpu) {
    cpu.AH = cpu.Status.Value & 0x00FF;
}

void I8086_SAHF(BYTE OpCode, I8086 &cpu) {
    cpu.Status.Value &= 0xFF00; // cut LSB part
    cpu.Status.Value |= cpu.AH;
}
