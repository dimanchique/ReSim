#include "MOS6502.h"
#include "MOS6502_OpHelpers.h"
#include "chrono"
#include <thread>

void MOS6502::Reset() noexcept {
    SP = 0xFF;

    Status.Value = 0;
    A = X = Y = 0;
    cycles = 0;
}

bool MOS6502::Step() {
    const BYTE opCode = FetchByte();
    return DecodeInstruction(opCode, *this);
}

U32 MOS6502::Run() {
    PC = (bus->Read(0xFFFD) << 8) | bus->Read(0xFFFC);
    U32 total_cycles = 0;
    std::chrono::steady_clock::time_point begin, end;
    double duration = 0;
    double sleep_needed = 0;
    bool decodeSuccess;

    constexpr double one_tick_duration = 1.0f / 5000000;

    do {
        cycles = 0;

        begin = std::chrono::steady_clock::now();
        decodeSuccess = Step();
        end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sleep_needed = cycles * one_tick_duration * 1000000;
        if (duration < sleep_needed) {
            std::chrono::microseconds real_duration(long(sleep_needed - duration));
            std::this_thread::sleep_for(real_duration);
        }

        total_cycles += cycles;
    } while (decodeSuccess);

    total_cycles--;     // revert false fetch cycles
    PC--;               // revert extra PC increment for last instruction fetching
    return total_cycles;
}
