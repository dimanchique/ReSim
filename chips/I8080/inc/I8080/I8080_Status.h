#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

#define I8080_Status_C          (1 << 0)
#define I8080_Status_P          (1 << 2)
#define I8080_Status_AC         (1 << 4)
#define I8080_Status_Z          (1 << 6)
#define I8080_Status_S          (1 << 7)

struct I8080_Status{
    BYTE C      :1;             // Carry Flag
    BYTE        :1;             // Not Used
    BYTE P      :1;             // Parity Flag
    BYTE        :1;             // Not Used
    BYTE AC     :1;             // Auxiliary Carry Flag
    BYTE        :1;             // Not Used
    BYTE Z      :1;             // Zero Flag
    BYTE S      :1;             // Sign Flag

    operator BYTE() noexcept {
        return *(BYTE *) (this);
    }

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

    FORCE_INLINE void SetAuxiliaryCarryFlagOfAdd(const BYTE firstOp, const BYTE secondOpWithCarry, const BYTE initialCarry = 0) {
        BYTE carryFlag = initialCarry;
        BYTE firstOpArg, secondOpArg;
        for(BYTE idx = 0; idx < 4; ++idx) {
            firstOpArg = (firstOp >> idx) & 0x01;
            secondOpArg = (secondOpWithCarry >> idx) & 0x01; // Consider the carry in the second operand
            carryFlag = ((firstOpArg + secondOpArg + carryFlag) >> 1) & 0x01;
        }
        AC = carryFlag;
    }
};
