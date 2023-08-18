#include "CPU6502.h"
#include "CPU6502_OpCodes.h"
#include "Memory.h"

int main() {
    Memory mem{64};
    CPU6502 cpu{};
    cpu.Reset(mem);

    // start
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0xF9;
    mem[0xFFFE] = 0xFF;
    mem[0xFFFA] = 0x42;
    mem[0xFFF9] = CPU6502_OpCodes::LDA_IM;
    //end
    cpu.Run(mem);
    return 0;
}