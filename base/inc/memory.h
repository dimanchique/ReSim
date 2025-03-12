#pragma once

#include <cstring>
#include <iostream>

#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"

struct Memory : public IO_Device {
  private:
    BYTE *mem;
    U32 size;

  public:
    explicit Memory(U32 memSize = 1) : size(memSize * 1024)
    {
        mem = new BYTE[size];
    }

    ~Memory() {
        delete[] mem;
    }

    void Reset() {
        memset(mem, 0xFF, size);
    }

    bool SetMemory(const char* data, long long int numBytes) {
        if (numBytes == 0 || (numBytes > size))
            return false;
        std::memcpy(mem, data, numBytes);
        return true;
    }

    FORCE_INLINE BYTE &operator[](U32 address) override {
        return mem[address];
    }

    FORCE_INLINE BYTE Read(U32 address) override {
        const BYTE value = mem[address];
        return value;
    }

    FORCE_INLINE void Write(U32 address, BYTE value) override {
        mem[address] = value;
    }
};
