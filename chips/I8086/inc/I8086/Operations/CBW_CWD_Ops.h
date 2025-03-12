#pragma once

#include "I8086/I8086.h"

void I8086_CBW(BYTE OpCode, I8086 &cpu) {
    cpu.AH = cpu.AL & 0x80 ? 0xFF : 0x00;
}

void I8086_CWD(BYTE OpCode, I8086 &cpu) {
    cpu.DX = cpu.AX & 0x8000 ? 0xFFFF : 0x0000;
}
