#pragma once

#include "I8086.h"

FORCE_INLINE void PerformLoop(I8086 &cpu, const bool conditionFlag = true) {
    const SWORD disp = (SWORD)cpu.Fetch<WORD>();
    cpu.CX--;
    if (conditionFlag && cpu.CX > 0)
        cpu.PC += disp;
}

void I8086_LOOP_Jb(BYTE, I8086 &cpu) {
    PerformLoop(cpu);
}

void I8086_LOOPZ_Jb(BYTE, I8086 &cpu) {
    PerformLoop(cpu, cpu.Status.Z);
}

void I8086_LOOPNZ_Jb(BYTE, I8086 &cpu) {
    PerformLoop(cpu, !cpu.Status.Z);
}
