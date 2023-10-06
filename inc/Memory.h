#pragma once

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
        for (U32 i = 0; i < size; ++i) {
            mem[i] = 0xFF;
        }
    }

private:
    BYTE *mem;
    U32 size;
};