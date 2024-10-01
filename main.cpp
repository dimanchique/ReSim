#include "chips/I8086/inc/I8086/I8086.h"

int main(int argc, char** argv) {
    I8086 cpu;
    Memory memory(1024);

    cpu.PC = 0x00;

    cpu.AX = 0x0060;
    cpu.DS = 0x4000;
    cpu.BX = 0x009A;

    memory[0x4009A] = 0x2C;
    memory[0x4009B] = 0x01;

    memory[0] = 0x09;
    memory[1] = 0x07;

    cpu.Run(memory);
    return 0;
}
