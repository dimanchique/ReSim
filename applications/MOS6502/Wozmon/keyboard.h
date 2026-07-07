#pragma once

#include <cstdio>
#include <mutex>
#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else

#include <unistd.h>
#include <termios.h>

#endif

char get_single_key() {
#ifdef _WIN32
    return _getch();
#else
    char ch = 0;
    struct termios old_opts, new_opts;
    tcgetattr(STDIN_FILENO, &old_opts);
    new_opts = old_opts;
    new_opts.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_opts);
    if (ch == 127)          // real backspace
        ch = (char) 0xDF;   // backspace for Wozmon
    else if (ch == 10)      // real enter
        ch = (char) 0x8D;   // enter for Wozmon
    return ch;
#endif
}

class Keyboard : public IO_Device<WORD> {
public:
    static constexpr WORD KEYBOARD_ADDR = 0xD010;
    static constexpr WORD KEYBOARD_STATUS = 0xD011;

    Keyboard() = default;

    void set_input(const char newInput) {
        std::lock_guard lock(input_mtx);
        input = newInput;
        input_ready = true;
    }

    FORCE_INLINE BYTE Read(WORD address) override {
        switch (address) {
            case KEYBOARD_STATUS: {
                std::lock_guard lock(input_mtx);
                return input_ready ? 0x80 : 0x00;
            }
            case KEYBOARD_ADDR: {
                std::lock_guard lock(input_mtx);
                input_ready = false;
                return input | 0x80;
            }
            default:
                return 0x00;
        }
    }

    FORCE_INLINE void Write(WORD address, BYTE value) override {}

    FORCE_INLINE BYTE &operator[](WORD address) override {
        static BYTE dummy = 0;
        return dummy;
    }

private:
    char input = '\0';
    bool input_ready = false;
    std::mutex input_mtx;
};
