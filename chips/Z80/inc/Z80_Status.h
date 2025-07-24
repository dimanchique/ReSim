#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

#define Z80_Status_C    (1 << 0)
#define Z80_Status_N    (1 << 1)
#define Z80_Status_PV   (1 << 2)
#define Z80_Status_H    (1 << 4)
#define Z80_Status_Z    (1 << 6)
#define Z80_Status_S    (1 << 7)

/**
 * @struct Z80_Status
 * @brief Z80 CPU Status register implementation.
 * @details Status register contains 6 status bits + 2 bit left unused.
 * The vast majority of instructions change Status Register state
 */
struct Z80_Status {
    union {
        struct {
            BYTE C: 1;             /**< Carry Flag */
            BYTE N: 1;             /**< Add/Subtract */
            BYTE PV: 1;             /**< Parity/Overflow Flag */
            BYTE        : 1;             /**< Not Used */
            BYTE H: 1;             /**< Half Carry Flag */
            BYTE        : 1;             /**< Not Used */
            BYTE Z: 1;             /**< Zero Flag */
            BYTE S: 1;             /**< Sign Flag */
        };
        BYTE Value;
    };

    /**
    * @brief Update status register using given value.
    * @details Function updates Zero, Sign, and Parity flags states.
    * @params value Input value to check.
    * @params mask Mask to define which bits to check.
    */
    FORCE_INLINE void UpdateStatusByValue(const BYTE &value, const BYTE mask) {
        if (mask & Z80_Status_Z)
            Z = (value == 0);
        if (mask & Z80_Status_S)
            S = (value & Z80_Status_S) > 0;
        if (mask & Z80_Status_PV) {
            BYTE bitCount = 0;
            for (BYTE idx = 0; idx < 8; ++idx) {
                if ((value >> idx) & 0x1)
                    bitCount++;
            }
            PV = ~(bitCount & 0x1);
        }
    }
};