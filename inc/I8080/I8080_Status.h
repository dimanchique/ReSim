#pragma once

#include "Types.h"
#include "Macro.h"

struct I8080_Status{

    BYTE C      :1;             // Carry Flag
    BYTE NU1    :1;             // Not Used
    BYTE P      :1;             // Parity Flag
    BYTE NU2    :1;             // Not Used
    BYTE AC     :1;             // Auxiliary Carry Flag
    BYTE NU3    :1;             // Not Used
    BYTE Z      :1;             // Zero Flag
    BYTE S      :1;             // Sign Flag

#define I8080_Status_C          (1 << 0)
#define I8080_Status_P          (1 << 2)
#define I8080_Status_AC         (1 << 4)
#define I8080_Status_Z          (1 << 6)
#define I8080_Status_S          (1 << 7)

    operator BYTE() const noexcept {
        return *(BYTE *) (this);
    }

    FORCE_INLINE I8080_Status &operator=(const BYTE referenceByte) {
        *(BYTE *) (this) = referenceByte;
        return *this;
    }

    FORCE_INLINE void UpdateStatusByValue(const BYTE &targetRegister, const BYTE mask) {
        if (mask & I8080_Status_Z)
            Z = (targetRegister == 0);
        if (mask & I8080_Status_S)
            S = (targetRegister & I8080_Status_S) > 0;
        if (mask & I8080_Status_P) {
            BYTE bitCount = 0;
            for(BYTE idx = 0; idx < 8; ++idx) {
                if ((targetRegister >> idx) & 0x1)
                    bitCount++;
            }
            P = ~(bitCount & 0x1);
        }
    }

    FORCE_INLINE void SetAuxiliaryCarryFlag(const BYTE &oldValue, const BYTE &newValue) {
        const bool oldAuxiliaryCarry = (oldValue >> 3) & 0x1;
        const bool newAuxiliaryCarry = (newValue >> 3) & 0x1;
        AC = oldAuxiliaryCarry ^ newAuxiliaryCarry;
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
