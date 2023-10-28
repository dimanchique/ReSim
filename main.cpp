#include "CPU6502.h"
#include <chrono>
#include <iostream>
#include <cassert>

int main() {
    CPU6502 cpu{};
    Memory mem{64};

    const bool loadSuccess = cpu.LoadROM("tools/asm_tests/CRC32_test.bin", mem, 0x3000);
    if(!loadSuccess)
        return -1;

    //testing data
    for(auto i = 0x1000; i < 0x1100; i++)
        mem[i] = 0x02;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    const auto n = cpu.Run(mem);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    const double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    assert(mem[0x06] == 0x64);
    assert(mem[0x07] == 0x80);
    assert(mem[0x08] == 0xDE);
    assert(mem[0x09] == 0xD4);

    std::cout << "Execution duration: " << duration / 1e6 << "[s]" << std::endl;
    std::cout << "Cycles count: " << n  << std::endl;
    std::cout << "Cycles/s: " << n / (duration / 1e6)  << std::endl;
    std::cout << "Frequency: " << n / duration << " MHz" << std::endl;
    return 0;
}