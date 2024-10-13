#include "chips/I8086/inc/I8086/I8086.h"

int main(int argc, char** argv) {
    I8086 cpu;
    Memory memory(1024);

    cpu.PC = 0x00;

    cpu.AX = 0x0060;
    cpu.DS = 0x4000;
    cpu.BX = 0x009A;
    cpu.BP = 0x1100;

    memory[0] = I8086_OpCodes::GRP1_Ev_Iv;
    memory[1] = 0b11001101;
    memory[2] = 0x00;
    memory[3] = 0x09;

    cpu.Run(memory);
    return 0;
}
