#pragma once
#include "Types.h"

struct CPU6502_Status{

    BYTE C  :1;             // Carry Flag
    BYTE Z  :1;             // Zero Flag
    BYTE I  :1;             // Interrupt Disable
    BYTE D  :1;             // Decimal Mode
    BYTE B  :1;             // Break Command
    BYTE NU :1;             // Not Used
    BYTE V  :1;             // Overflow Flag
    BYTE N  :1;             // Negative Flag

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

    CPU6502_Status &operator=(const BYTE referenceByte) {
        *(BYTE *) (this) = referenceByte;
        return *this;
    }

    inline void UpdateStatusByValue(const BYTE &targetRegister, const BYTE mask) {
        if (mask & CPU6502_Status_Z)
            Z = (targetRegister == 0);
        if (mask & CPU6502_Status_N)
            N = (targetRegister & CPU6502_Status_N) > 0;
    }

    [[nodiscard]] inline bool GetStatusValue(const BYTE checkArgs) const noexcept {
        return static_cast<BYTE>(*this) & checkArgs;
    }

    inline void SetStatusFlagValue(const BYTE statusFlag, const bool value) noexcept {
        if (value)
            *(BYTE *) (this) |= statusFlag;
        else
            *(BYTE *) (this) &= ~statusFlag;
    }
};
