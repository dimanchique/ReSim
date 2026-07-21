#pragma once

#include <cstdio>
#include <mutex>
#include <queue>
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

    if (ch == 27)                   // esc
        ch = (char) 0x1A;           // cp-m esc
    else if (ch == 127)             // backspace
        ch = (char) 0x08;           // cp-m backspace
    else if (ch == 4)               // ctrl-D
        ch = (char) 0x03;           // cp-m ctrl-c
    else if (ch == '\n')            // enter
        ch = (char) 0x0D;           // cp-m enter
    return ch;
#endif
}

class Keyboard : public IO_Device<WORD> {
public:
    static constexpr WORD KEYBOARD_STATUS = 0x00;
    static constexpr WORD KEYBOARD_DATA = 0x01;

    Keyboard() = default;

    void set_input(const char ch) {
        std::lock_guard lock(input_mtx);
        input = ch;
    }

    FORCE_INLINE BYTE Read(WORD address) override {
        switch (address) {
            case KEYBOARD_STATUS: {
                std::lock_guard lock(input_mtx);
                return (input == '\0') ? 0x00 : 0xFF;
            }
            case KEYBOARD_DATA: {
                std::lock_guard lock(input_mtx);
                if (input == '\0') return 0x00;
                char ch = input;
                input = '\0';
                return ch;
            }
            default:
                return 0x00;
        }
    }

    FORCE_INLINE void Write(WORD address, BYTE value) override {}

private:
    char input = '\0';
    std::mutex input_mtx;
};
