#pragma once

struct Memory {
    explicit Memory(U32 mem_size = 1) : size(mem_size * 1024) {
        mem = new BYTE[size];
    }

    ~Memory() {
        delete[] mem;
    }

    BYTE operator[](U32 addr) const {
        return mem[addr];
    }

    BYTE &operator[](U32 addr) {
        return mem[addr];
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