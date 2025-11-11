#pragma once

#include "core/compilers_macro.h"
#include "core/types.h"

namespace ReSimFunctionLibrary::DataManipulation {
    FORCE_INLINE WORD putTwoBytesToLIWord(const BYTE& msbReg, const BYTE& lsbReg) noexcept {
        return (msbReg << 8) | lsbReg;
    }

    FORCE_INLINE WORD swapWord(const WORD& value) noexcept {
        return ((value << 8) & 0xFF00) | ((value >> 8) & 0xFF);
    }

    FORCE_INLINE void putLIWordToTwoBytes(const WORD value, BYTE& lsbReg, BYTE& msbReg) noexcept {
        msbReg = value & 0xFF;
        lsbReg = (value >> 8) & 0xFF;
    }
}
