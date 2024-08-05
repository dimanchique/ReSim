#include "MOS6502/MOS6502.h"

int main(int argc, char** argv) {
    Memory mem{64};
    MOS6502 cpu{};

    cpu.LoadROM("C:/Users/dimanchique/Desktop/a.out", mem);
    cpu.Run(mem);
    return 0;
}