#pragma once
#include <Types.h>

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

    BYTE ReadByte(S32 &Cycles, WORD ADDR) const{
        BYTE Data = MEM[ADDR];
        Cycles--;
        return Data;
    }

    WORD ReadWord(S32 &Cycles, WORD ADDR) const{
        BYTE Lo = ReadByte(Cycles, ADDR);
        BYTE Hi = ReadByte(Cycles, ADDR + 1);
        return Lo | (Hi << 8);
    }

    void WriteByte(S32 &Cycles, BYTE Value, U32 ADDR){
        MEM[ADDR] = Value;
        Cycles --;
    }

    void WriteWord(S32 &Cycles, WORD Value, U32 ADDR){
        MEM[ADDR] = Value & 0xFF;
        MEM[ADDR + 1] = (Value >> 8);
        Cycles -= 2;
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