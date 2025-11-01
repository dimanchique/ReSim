#pragma once

#include "I8086.h"

void I8086_XLAT(BYTE, I8086& cpu) {
    WORD offsetValue = cpu.AL + cpu.BX;
    cpu.AL = cpu.ReadByte(EFFECTIVE_ADDRESS(offsetValue, cpu.DS));
}
