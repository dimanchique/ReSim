#include "MOS6502.h"
#include "memory.h"
#include "bus.h"
#include "keyboard.h"
#include "tty.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <filesystem>

std::atomic<bool> g_running{true};
std::string g_pending_input;

void keyboard_thread(Keyboard* kbd) {
    while (g_running) {
        std::string line;
        if (std::getline(std::cin, line)) {
            if (line == "quit" || line == "q") {
                g_running = false;
                break;
            }
            g_pending_input += line;
            kbd->set_input(g_pending_input.c_str());
            g_pending_input = "";
            std::cout << "\033[F";
        } else {
            g_running = false;
            break;
        }
    }
}

int main(int argc, char** argv) {
    const std::filesystem::path projectRoot = SOURCE_DIR;
    const std::filesystem::path filePath = projectRoot / "ehbasic.bin";

    Memory<WORD> mem(64);
    mem.Reset();

    Bus<WORD> bus;
    Keyboard kbd;
    TTY tty;
    MOS6502 cpu;

    bus.SetBusRegion(0x0000, 0xFFFF, &mem);
    bus.SetBusRegion(Keyboard::KEYBOARD_ADDR, Keyboard::KEYBOARD_ADDR, &kbd);
    bus.SetBusRegion(TTY::TTY_OUTPUT, TTY::TTY_OUTPUT, &tty);

    cpu.LoadROM(filePath.c_str(), mem);
    cpu.SetBusInstance(&bus);
    mem[0xFFFC] = 0x80;
    mem[0xFFFD] = 0xFF;

// MONRDKEY at $FD0C
// Wrap for keyboard input
    mem[0xFD0C] = 0xAD;  // LDA abs
    mem[0xFD0D] = 0x00;  // $D100 low
    mem[0xFD0E] = 0xD1;  // $D100 high
    mem[0xFD0F] = 0x60;  // RTS

// MONCOUT at $FDED
// Wrap for tty output
    mem[0xFDED] = 0x8D;  // STA abs
    mem[0xFDEE] = 0x01;  // $D101 low
    mem[0xFDEF] = 0xD1;  // $D101 high
    mem[0xFDF0] = 0x60;  // RTS

    U32 cycles = 0;
    std::thread kb_thread(keyboard_thread, &kbd);
    std::thread cpu_thread([&cpu, &cycles](){ cycles = cpu.Run(); });

    while (g_running) {}
    cpu.Stop();
    kb_thread.join();
    cpu_thread.join();

    return 0;
}
