#pragma once

#include "I8086.h"

void I8086_AAA(BYTE, I8086& cpu) {
    if ((cpu.AL & 0x0F) > 9 || cpu.Status.A ){
        cpu.AL += 6;
        cpu.AH += 1;
        cpu.Status.C = 1;
        cpu.Status.A = 1;
    }
    else {
        cpu.Status.C = 0;
        cpu.Status.A = 0;
    }
    cpu.AL = cpu.AL & 0x0F;
}

void I8086_AAS(BYTE, I8086& cpu) {
    if ((cpu.AL & 0x0F) > 9 || cpu.Status.A ){
        cpu.AL -= 6;
        cpu.AH -= 1;
        cpu.Status.C = 1;
        cpu.Status.A = 1;
    }
    else {
        cpu.Status.C = 0;
        cpu.Status.A = 0;
    }
    cpu.AL = cpu.AL & 0x0F;
}

void I8086_AAM(BYTE, I8086& cpu) {
    cpu.AH = cpu.AL / 0x0A;
    cpu.AL = cpu.AL % 0x0A;

    cpu.Status.UpdateStatusByValue(cpu.AL, I8086_Status_P | I8086_Status_Z | I8086_Status_S);
}

void I8086_AAD(BYTE, I8086& cpu) {
    cpu.AL = cpu.AL + (cpu.AH * 0x0A);
    cpu.AH = 0;

    cpu.Status.UpdateStatusByValue(cpu.AL, I8086_Status_P | I8086_Status_Z | I8086_Status_S);
}
