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

void keyboard_thread(Keyboard *kbd) {
    while (g_running) {
        if (char input = get_single_key()) {
            kbd->set_input(input);
        } else {
            g_running = false;
            break;
        }
    }
}

int main(int argc, char **argv) {
    const std::filesystem::path projectRoot = SOURCE_DIR;
    const std::filesystem::path filePath = projectRoot / "ehbasic.bin";

    Memory<WORD> mem(64);
    mem.Reset();

    Bus<WORD> bus;
    Keyboard kbd;
    TTY tty;
    MOS6502 cpu;

    bus.Attach(&mem, 0x0000, 0xFFFF);
    bus.Attach(&kbd, Keyboard::KEYBOARD_ADDR, Keyboard::KEYBOARD_ADDR);
    bus.Attach(&tty, TTY::TTY_OUTPUT, TTY::TTY_OUTPUT);

    cpu.LoadROM(filePath.c_str(), mem);
    cpu.SetBusInstance(&bus);

    U32 cycles = 0;
    std::thread kb_thread(keyboard_thread, &kbd);
    std::thread cpu_thread([&cpu, &cycles]() { cycles = cpu.Run(); });

    while (g_running) {}
    cpu.Stop();
    kb_thread.join();
    cpu_thread.join();

    return 0;
}
