#pragma once

#include "core/types.h"
#include "core/macro.h"

#define MOS6502_Status_C    (1 << 0)
#define MOS6502_Status_Z    (1 << 1)
#define MOS6502_Status_I    (1 << 2)
#define MOS6502_Status_D    (1 << 3)
#define MOS6502_Status_B    (1 << 4)
#define MOS6502_Status_V    (1 << 6)
#define MOS6502_Status_N    (1 << 7)

struct MOS6502_Status{
    BYTE C  :1;             // Carry Flag
    BYTE Z  :1;             // Zero Flag
    BYTE I  :1;             // Interrupt Disable
    BYTE D  :1;             // Decimal Mode
    BYTE B  :1;             // Break Command
    BYTE NU :1;             // Not Used
    BYTE V  :1;             // Overflow Flag
    BYTE N  :1;             // Negative Flag

    operator BYTE() noexcept {
        return *(BYTE *) (this);
    }

    operator BYTE() const noexcept {
        return *(BYTE *) (this);
    }

    FORCE_INLINE MOS6502_Status &operator=(const BYTE referenceByte) {
        *(BYTE *) (this) = referenceByte;
        NU = 0; // this flag is immutable
        return *this;
    }

    FORCE_INLINE void UpdateStatusByValue(const BYTE &targetRegister, const BYTE mask) {
        if (mask & MOS6502_Status_Z)
            Z = (targetRegister == 0);
        if (mask & MOS6502_Status_N)
            N = (targetRegister & MOS6502_Status_N) > 0;
    }

    FORCE_INLINE bool GetStatusValue(const BYTE checkArgs) const noexcept {
        return static_cast<BYTE>(*this) & checkArgs;
    }

    FORCE_INLINE void SetStatusFlagValue(const BYTE statusFlag, const bool value) noexcept {
        if (value)
            *(BYTE *) (this) |= statusFlag;
        else
            *(BYTE *) (this) &= ~statusFlag;
    }
};
