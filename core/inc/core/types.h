#pragma once

#include <cstdint>

enum class OperandSize {
    BYTE, WORD, SWORD, DWORD, QWORD
};

using BYTE  = uint8_t ;
using SBYTE = int8_t  ;
using WORD  = uint16_t;
using SWORD = int16_t;
using DWORD = uint32_t;
using QWORD = uint64_t;

using U32   = uint32_t;
using S32   = int32_t ;
