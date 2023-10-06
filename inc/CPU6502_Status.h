#pragma once
#include <cstring>
#include "Types.h"

struct CPU6502_Status{

//  Processor Status
    BYTE C  :1;             // Carry Flag
    BYTE Z  :1;             // Zero Flag
    BYTE I  :1;             // Interrupt Disable
    BYTE D  :1;             // Decimal Mode
    BYTE B  :1;             // Break Command
    BYTE NU :1;             // Not Used
    BYTE V  :1;             // Overflow Flag
    BYTE N  :1;             // Negative Flag

//  Status Register Mask
#define CPU6502_Status_C    (1 << 0)
#define CPU6502_Status_Z    (1 << 1)
#define CPU6502_Status_I    (1 << 2)
#define CPU6502_Status_D    (1 << 3)
#define CPU6502_Status_B    (1 << 4)
#define CPU6502_Status_V    (1 << 6)
#define CPU6502_Status_N    (1 << 7)

    operator BYTE() const noexcept {
        return *(BYTE *) (this);
    }

    void Reset() noexcept {
        *this = 0;
    }

    CPU6502_Status &operator=(const BYTE referenceByte) {
        memset(this, referenceByte, 1);
        return *this;
    }

    void UpdateStatus(const BYTE &targetRegister, BYTE mask) {
        if (mask & CPU6502_Status_Z)
            Z = (targetRegister == 0);
        if (mask & CPU6502_Status_N)
            N = (targetRegister & 0b10000000) > 0;
    }

    [[nodiscard]] bool GetStatusValue(BYTE checkArgs) const noexcept {
        return BYTE(*this) & checkArgs;
    }

    void SetStatusFlagValue(BYTE statusFlag, BYTE value) noexcept {
        if (value)
            SetFlag(statusFlag);
        else
            ResetFlag(statusFlag);
    }

    void SetFlag(BYTE mask) noexcept {
        *(BYTE *) (this) |= mask;
    }

    void ResetFlag(BYTE mask) noexcept {
        *(BYTE *) (this) &= ~mask;
    }
};
