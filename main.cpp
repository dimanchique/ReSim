#include <filesystem>
#include <vector>
#include <thread>
#include "MOS6502.h"
#include "MOS6502_OpCodes_Main.h"

class TTY_Prototype : public IO_Device {
public:

    FORCE_INLINE BYTE &operator[](U32 address) override {
        return last_char;
    }

    FORCE_INLINE BYTE Read(U32 address) override {
        return last_char;
    }

    FORCE_INLINE void Write(U32 address, BYTE value) override {
        if (value == 0)
            return;

        if (value & 0x80)
            last_char = value - 0x80;
        else
            last_char = value;
        if (last_char != 127) {
            if (last_char == '\r') {
                std::printf("\n");
            } else {
                std::printf("%c", last_char);
            }
        }
        last_char = 0;
    }

private:
    BYTE last_char = 0;
};

class Keyboard_Prototype : public IO_Device {
public:

    FORCE_INLINE BYTE &operator[](U32 address) override {
        return buffer[0];
    }

    FORCE_INLINE BYTE Read(U32 address) override {
        if (address == 0xD011)
            return isBufferReady ? 0x80 : 0x00;

        if (!isBufferReady)
            return 0;

        BYTE ch = buffer[0];
        buffer = std::vector<BYTE>(buffer.begin() + 1, buffer.end());
        if (buffer.empty()) {
            isBufferReady = false;
        }
        if (ch == 0x8D)
            std::printf("\n");
        return ch | 0x80;
    }

    FORCE_INLINE void Write(U32 address, BYTE value) override {
    }

    void Run() {
        kbd_th = std::thread(&Keyboard_Prototype::Update, this);
        kbd_th.detach();
    }

    void Stop() {
        bTerminated = true;
        kbd_th.join();
    }

    void Update() {
        while (!bTerminated) {
            char line[100] = {0}; // Make it large enough.
            while( fgets(line, 100, stdin))
            {
                buffer.clear();
                for(char & i : line) {
                    if (i && i != '\n') {
                        buffer.emplace_back(i);
                    }
                    else break;
                }
                if (!buffer.empty()) {
                    buffer.emplace_back(0x8D);
                    isBufferReady = true;
                }
            }
        }
    }

private:
    std::thread kbd_th;
    bool bTerminated = false;
    bool isBufferReady = false;
    std::vector<BYTE> buffer{};
};

int main(int argc, char** argv) {
    MOS6502 cpu;
    Memory memory(64);
    TTY_Prototype tty{};
    Keyboard_Prototype kbd{};
    Bus bus{};
    cpu.SetBusInstance(&bus);
    bus.SetBusRegion(0x0000, 0xFFFF, &memory);
    bus.SetBusRegion(0xD012, 0xD012, &tty);
    bus.SetBusRegion(0xD010, 0xD011, &kbd);

    std::filesystem::path filePath = "/home/dimanchique/Downloads/a.out";
    cpu.LoadROM(filePath.generic_string().c_str(), memory);

    kbd.Run();
    cpu.Run();
    return 0;
}
