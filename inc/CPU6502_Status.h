#pragma once

#include <cstring>
#include "Types.h"

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

    void SetStatusFlagValue(BYTE Value, BYTE StatusFlag){
        if(Value)
            SetFlag(StatusFlag);
        else
            ResetFlag(StatusFlag);
    }

    void SetFlag(BYTE StatusFlag){
        *(BYTE*)(this) |= StatusFlag;
    }

    void ResetFlag(BYTE StatusFlag){
        *(BYTE*)(this) &= ~StatusFlag;
    }
};
