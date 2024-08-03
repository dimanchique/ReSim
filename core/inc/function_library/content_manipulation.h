#pragma once

#include "core/compilers_macro.h"
#include "core/types.h"

namespace ReSimFunctionLibrary::ContentManipulation{

    static constexpr FORCE_INLINE WORD getWordAsSwappedBytes_Copy(const BYTE& lsbReg, const BYTE& msbReg) {
        WORD value = 0;
        value |= lsbReg << 8;
        value |= msbReg;
        return value;
    }

    static FORCE_INLINE void putWordToBytesSwapped_Ref(const WORD value, BYTE& lsbReg, BYTE& msbReg) {
        msbReg = value & 0xFF;
        lsbReg = (value >> 8) & 0xFF;
    }

}
