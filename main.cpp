#include <vector>
#include <fstream>
#include "CPU6502.h"
#include <chrono>
#include <iostream>
#include <cassert>

//#define CRC16TEST
#define CRC32TEST

static std::vector<char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    if (pos == 0)
        return std::vector<char>{};

    std::vector<char> result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

int main() {
#ifdef CRC16TEST
    const auto data = ReadAllBytes("tools/asm_tests/CRC16_test.bin");
#else
    const auto data = ReadAllBytes("tools/asm_tests/CRC32_test.bin");
#endif

    CPU6502 cpu{};
    Memory mem{64};

    cpu.Reset(mem, 0x3000);
    for(auto i = 0; i < data.size(); i++)
        mem[0x3000 + i] = data[i];

    for(auto i = 0x1000; i < 0x1100; i++)
        mem[i] = 0x02;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    const auto n = cpu.Run(mem);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    const double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

#ifdef CRC16TEST
    assert(mem[0x06] == 0xA1);
    assert(mem[0x07] == 0xF1);
#else
    assert(mem[0x06] == 0x64);
    assert(mem[0x07] == 0x80);
    assert(mem[0x08] == 0xDE);
    assert(mem[0x09] == 0xD4);
#endif

    std::cout << "Execution duration: " << duration / 1e6 << "[s]" << std::endl;
    std::cout << "Cycles count: " << n  << std::endl;
    std::cout << "Cycles/s: " << n / (duration / 1e6)  << std::endl;
    std::cout << "Frequency: " << n / duration << " MHz" << std::endl;
    return 0;
}