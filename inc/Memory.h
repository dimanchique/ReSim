#pragma once
#include <Types.h>
#include <vector>

struct Memory {
    explicit Memory(U32 MEM_SIZE = 1) : SIZE(MEM_SIZE * 1024) {
        MEM.resize(SIZE);
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

    [[nodiscard]] U32 GetSize() const noexcept {
        return SIZE;
    }

private:
    std::vector<BYTE> MEM;
    U32 SIZE;
};