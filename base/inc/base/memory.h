#pragma once

#include "core/types.h"

struct Memory {
  private:
    BYTE *mem;
    U32 size;
  public:

    explicit Memory(U32 memSize = 1);
    ~Memory();

    void Reset(const BYTE resetValue);

    bool SetMemory(U32 address, const char* data, long long int numBytes);


    FORCE_INLINE BYTE operator[](U32 address) const {
        return mem[address];
    }
    FORCE_INLINE BYTE &operator[](U32 address) {
        return mem[address];
    }
};
