#pragma once

#include <cstdio>
#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"

class TTY : public IO_Device<WORD> {
public:
    static constexpr WORD TTY_OUTPUT = 0xD012;

    TTY() = default;

    FORCE_INLINE BYTE Read(WORD address) override {
        return 0x00;
    }

    FORCE_INLINE void Write(WORD address, BYTE value) override {
        char c = static_cast<char>(value & 0x7F);
        if (c == 0x08) // EhBASIC backspace echo
        {
            putchar('\b');             // move cursor left
            putchar(' ');              // overwrite with space
        }
        putchar(c);
        fflush(stdout);
    }

    FORCE_INLINE BYTE &operator[](WORD address) override {
        static BYTE dummy = 0;
        return dummy;
    }
};
