#pragma once

#include <cstring>
#include <iostream>

#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"

template<typename BusWidth>
class Memory : public IO_Device<BusWidth> {
private:
    BYTE *mem;
    BusWidth size;

public:
    explicit Memory(BusWidth memSize = 1) : size(memSize * 1024 - 1) {
        mem = new BYTE[size];
    }

    ~Memory() {
        delete[] mem;
    }

    void Reset() {
        memset(mem, 0xFF, size);
    }

    bool SetMemory(const char *data, long long int numBytes) {
        if (numBytes > size)
            numBytes = size;
        if (numBytes == 0)
            return false;
        std::memcpy(mem, data, numBytes);
        return true;
    }

    FORCE_INLINE BYTE &operator[](BusWidth address) override {
        return mem[address];
    }

    FORCE_INLINE BYTE Read(BusWidth address) override {
        return mem[address];
    }

    FORCE_INLINE void Write(BusWidth address, BYTE value) override {
        mem[address] = value;
    }
};
