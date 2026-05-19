#pragma once

#include <cstdio>
#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"

class Keyboard : public IO_Device<WORD> {
public:
    static constexpr WORD KEYBOARD_ADDR = 0xD010;
    static constexpr WORD KEYBOARD_STATUS = 0xD011;

    Keyboard() : buffer_pos(0), buffer_len(0) {
        input_buffer[0] = '\0';
    }

    void set_input(const char* text) {
        while (*text && buffer_len < 254) {
            input_buffer[buffer_len++] = *text++;
        }
        input_buffer[buffer_len++] = '\r';
        input_buffer[buffer_len] = '\0';
    }

    FORCE_INLINE BYTE Read(WORD address) override {
        switch (address) {
            case KEYBOARD_STATUS:
                return (buffer_pos < buffer_len) ? 0x80 : 0x00;
            case KEYBOARD_ADDR:
                return get_key();
            default:
                return 0x00;
        }
    }

    FORCE_INLINE void Write(WORD address, BYTE value) override { }

    FORCE_INLINE BYTE& operator[](WORD address) override {
        static BYTE dummy = 0;
        return dummy;
    }

private:
    BYTE get_key() {
        if (buffer_pos < buffer_len) {
            BYTE key = input_buffer[buffer_pos++];
            if (key == '\r' || key == '\n') key = 0x8D;
            return key | 0x80;
        }
        return 0x00;
    }

    char input_buffer[256];
    size_t buffer_pos;
    size_t buffer_len;
};
