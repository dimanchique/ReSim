#pragma once

#include <cstdio>
#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"

#ifdef _WIN32
#include <conio.h>
#else

#include <unistd.h>
#include <termios.h>
#include <mutex>

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
        ch = (char) 0x08;   // backspace for EhBASIC
    else if (ch == 27)      // real esc
        ch = (char) 0x03;   // ctrl-c for EhBASIC
    else if (ch == 10)      // real enter
        ch = (char) 0x8D;   // enter for EhBASIC
    return ch;
#endif
}

class Keyboard : public IO_Device<WORD> {
public:
    static constexpr WORD KEYBOARD_ADDR = 0xD010;

    Keyboard() {}

    void set_input(const char newInput) {
        std::lock_guard lock(input_mtx);
        input = newInput;
        input_ready = true;
    }

    FORCE_INLINE BYTE Read(WORD address) override {
        switch (address) {
            case KEYBOARD_ADDR: {
                std::lock_guard lock(input_mtx);
                if (input_ready) {
                    input_ready = false;
                    return input | 0x80;
                }
                return 0x00;
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
