#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

#define I8086_Status_C          (1 << 0)
#define I8086_Status_P          (1 << 2)
#define I8086_Status_A          (1 << 4)
#define I8086_Status_Z          (1 << 6)
#define I8086_Status_S          (1 << 7)
#define I8086_Status_T          (1 << 8)
#define I8086_Status_I          (1 << 9)
#define I8086_Status_D          (1 << 10)
#define I8086_Status_O          (1 << 11)

struct I8086_Status{
    WORD C      :1;             // Carry Flag
    WORD NU1    :1;             // Not Used
    WORD P      :1;             // Parity Flag
    WORD NU2    :1;             // Not Used
    WORD A      :1;             // Auxiliary Carry Flag
    WORD NU3    :1;             // Not Used
    WORD Z      :1;             // Zero Flag
    WORD S      :1;             // Sign Flag
    WORD T      :1;             // Trap Flag
    WORD I      :1;             // Interrupt Flag
    WORD D      :1;             // Direction Flag
    WORD O      :1;             // Overflow Flag
    WORD NU4    :4;             // Not Used

    operator WORD() noexcept {
        return *(WORD *) (this);
    }

    operator WORD() const noexcept {
        return *(WORD *) (this);
    }

    FORCE_INLINE I8086_Status &operator=(const WORD referenceByte) {
        *(WORD *) (this) = referenceByte;
        NU1 = 1; // these flags are immutable
        NU2 = 0;
        NU3 = 0;
        NU4 = 0;
        return *this;
    }

    FORCE_INLINE void UpdateStatusByValue(const BYTE &targetRegister, const BYTE mask) {
        if (mask & I8086_Status_Z)
            Z = (targetRegister == 0);
        if (mask & I8086_Status_S)
            S = (targetRegister & I8086_Status_S) > 0;
        if (mask & I8086_Status_P) {
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
        A = carryFlag;
    }
};
