#include <chrono>
#include <thread>
#ifdef PRINT_DIAGNOSTICS
#include <iomanip>
#endif
#include "I8080.h"
#include "I8080_OpHelpers.h"

void I8080::Reset() noexcept {
    PC = 0x0000;
    SP = 0xFFFF;
    Status.Value = 0;

    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;
}

bool I8080::Step() {
#ifdef PRINT_DIAGNOSTICS
    std::cout << std::hex
              << std::setfill('0')
              << std::setw(4)
              << PC << ": ";
#endif
    const BYTE opCode = FetchByte();
    return DecodeInstruction(opCode, *this);
}

U32 I8080::Run() {
    U32 total_cycles = 0;
    std::chrono::steady_clock::time_point begin, end;
    double duration = 0;
    double sleep_needed = 0;
    bool decodeSuccess;

#ifdef PRINT_DIAGNOSTICS
    constexpr double one_tick_duration = 1.0f / 50000;
#else
    constexpr double one_tick_duration = 1.0f / 5000000;
#endif

    do {
        cycles = 0;

        begin = std::chrono::steady_clock::now();

#ifdef PRINT_DIAGNOSTICS
        WORD prevPC = PC;
#endif
        decodeSuccess = Step();
#ifdef PRINT_DIAGNOSTICS
        WORD newPC = PC;
        WORD size = newPC - prevPC;
        size = size >= 3 ? 3 : size;

        for (BYTE i = 1; i < size; i++) {
            std::cout << std::hex
                      << std::setfill('0')
                      << std::setw(2) << (int) bus->Read(prevPC + i) << " ";
        }
        std::cout << "\n";
#endif

        end = std::chrono::steady_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        sleep_needed = cycles * one_tick_duration * 1000000;
        if (duration < sleep_needed) {
            std::chrono::microseconds real_duration(long(sleep_needed - duration));
            std::this_thread::sleep_for(real_duration);
        }

        total_cycles += cycles;
    } while (decodeSuccess && !stop_requested);

    total_cycles -= 3;  // revert false fetch cycles
    PC--;               // revert extra PC increment for last instruction fetching
    return total_cycles;
}
