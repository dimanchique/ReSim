#pragma once

#include <cstring>
#include "Types.h"

struct Memory;

struct CPU6502_Status{
//**********************************************************
//                          Processor Status
//**********************************************************
    BYTE C  :1;             // Carry Flag
    BYTE Z  :1;             // Zero Flag
    BYTE I  :1;             // Interrupt Disable
    BYTE D  :1;             // Decimal Mode
    BYTE B  :1;             // Break Command
    BYTE NU :1;             // Not Used
    BYTE V  :1;             // Overflow Flag
    BYTE N  :1;             // Negative Flag
//**********************************************************
//                          Status Register Mask
//**********************************************************
#define CPU6502_Status_C    (1 << 0)
#define CPU6502_Status_Z    (1 << 1)
#define CPU6502_Status_I    (1 << 2)
#define CPU6502_Status_D    (1 << 3)
#define CPU6502_Status_B    (1 << 4)
#define CPU6502_Status_V    (1 << 6)
#define CPU6502_Status_N    (1 << 7)
//**********************************************************
    operator BYTE() const {
        return *(BYTE*)(this);
    }

    void Reset(){
        *this = 0;
    }

    CPU6502_Status& operator=(const BYTE ReferenceByte){
        memset(this, ReferenceByte, 1);
        return *this;
    }

    void SetStatusValue(BYTE& Register, BYTE CheckArgs){
        if(CheckArgs & CPU6502_Status_Z)
            Z = (Register == 0);
        if(CheckArgs & CPU6502_Status_N)
            N = (Register & 0b10000000) > 0;
    }

    bool GetStatusValue(BYTE CheckArgs) const{
        return BYTE(*this) & CheckArgs;
    }

    void SetFlag(BYTE StatusFlag){
        *(BYTE*)(this) |= StatusFlag;
    }

    void ClearFlag(BYTE StatusFlag){
        *(BYTE*)(this) &= ~StatusFlag;
    }
};

struct CPU6502 {
//**********************************************************
//                          Registers
//**********************************************************
    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE X;                 // X Index
    BYTE Y;                 // Y Index
    CPU6502_Status Status;
//**********************************************************
//                          Functions
//**********************************************************
    void Reset(Memory &Memory);
    void Reset(WORD ResetVector, Memory& Memory);

    BYTE FetchByte(U32 &Cycles, const Memory &Memory);
    WORD FetchWord(U32 &Cycles, const Memory &Memory);

    BYTE ReadByte(U32 &Cycles, const Memory &Memory, WORD ADDR) const;
    WORD ReadWord(U32 &Cycles, const Memory &Memory, WORD ADDR) const;

    void WriteByte(U32 &Cycles, Memory &Memory, BYTE Value, U32 ADDR);
    void WriteWord(U32 &Cycles, Memory &Memory, WORD Value, U32 ADDR);

    void PushProgramCounterToStack(U32 &Cycles, Memory &Memory);
    WORD PopAddressFromStack(U32 &Cycles, Memory &Memory);

    void PushByteToStack(U32 &Cycles, Memory &Memory, BYTE Value);
    void PushWordToStack(U32 &Cycles, Memory &Memory, WORD Value);

    BYTE PullByteFromStack(U32 &Cycles, Memory &Memory);
    WORD PullWordFromStack(U32 &Cycles, Memory &Memory);

    U32 Run(Memory &Memory);

    WORD StackPointerToAddress() const {
        return 0x100 | SP;
    }

    void SetStatusValue(BYTE& Register, BYTE CheckArgs){
        Status.SetStatusValue(Register, CheckArgs);
    }
};
