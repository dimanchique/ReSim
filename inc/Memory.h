#pragma once
#include <utils.h>

struct Memory {
    explicit Memory(U32 MEM_SIZE = 1) : SIZE(MEM_SIZE * 1024) {
        MEM = new BYTE[SIZE];
    }

    ~Memory(){
        delete[] MEM;
    }

    BYTE operator[](U32 ADDR) const {
        return MEM[ADDR];
    }

    BYTE &operator[](U32 ADDR) {
        return MEM[ADDR];
    }

    void Reset() {
        for (U32 i = 0; i < SIZE; ++i) {
            MEM[i] = 0;
        }
    }

private:
    BYTE* MEM;
    U32 SIZE;
};