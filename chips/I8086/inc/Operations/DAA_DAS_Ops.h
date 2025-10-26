#pragma once

void I8086_DAA(BYTE, I8086 &cpu) {
    if ((cpu.AL & 0x0F) > 9 || cpu.Status.A) {
        cpu.AL += 6;
        cpu.Status.A = 1;
    }
    if (cpu.AL > 0x9F || cpu.Status.C) {
        cpu.AL += 0x60;
        cpu.Status.C = 1;
    }

    cpu.Status.UpdateStatusByValue(cpu.AL, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

void I8086_DAS(BYTE, I8086 &cpu) {
    if ((cpu.AL & 0x0F) > 9 || cpu.Status.A) {
        cpu.AL -= 6;
        cpu.Status.A = 1;
    }
    if (cpu.AL > 0x9F || cpu.Status.C) {
        cpu.AL -= 0x60;
        cpu.Status.C = 1;
    }

    cpu.Status.UpdateStatusByValue(cpu.AL, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}
