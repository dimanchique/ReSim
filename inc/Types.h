#pragma once

using BYTE = unsigned char;
using SBYTE = signed char;
using WORD = unsigned short;
using U32 = unsigned int;
using S32 = int;

/**
 * @brief Compact structure for a 16-bit value and its high and low bytes.
 *
 * This structure allows convenient access to a 16-bit value as a whole (WORD),
 * as well as its high and low bytes individually (BYTE).
 */
struct BiRegister {
    union {
        WORD Value;
        struct {
            BYTE H;
            BYTE L;
        };
    };

    BiRegister& operator=(const WORD& value) {
        Value = value;
        return *this;
    }

    BiRegister& operator=(const BiRegister& other) {
        Value = other.Value;
        return *this;
    }

    WORD AsBigEndianWord() const {
        WORD resultWord = 0;
        resultWord |= L << 8;
        resultWord |= H;
        return resultWord;
    }
};