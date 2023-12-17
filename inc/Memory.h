#pragma once

#include <cstring>

struct Memory {
    explicit Memory(U32 memSize = 1) : size(memSize * 1024) {
        mem = new BYTE[size];
    }

    ~Memory() {
        delete[] mem;
    }

    BYTE operator[](U32 address) const {
        return mem[address];
    }

    BYTE &operator[](U32 address) {
        return mem[address];
    }

    void Reset() {
        memset(mem, 0xFF, size);
    }

    bool SetMemory(U32 address, const char* data, long long int numBytes) {
        if(address + numBytes >= size)
            return false;
        memcpy(mem + address, data, numBytes);
        return true;
    }

private:
    BYTE *mem;
    U32 size;
};