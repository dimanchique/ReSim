#pragma once

#define PAGE_SIZE 0xff

using BYTE = unsigned char;
using SBYTE = signed char;
using WORD = unsigned short;
using U32 = unsigned int;
using S32 = int;

struct ValueAddressRequest {
    BYTE Value;
    WORD Address;
};