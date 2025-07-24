#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

#define MOS6502_Status_C    (1 << 0)
#define MOS6502_Status_Z    (1 << 1)
#define MOS6502_Status_I    (1 << 2)
#define MOS6502_Status_D    (1 << 3)
#define MOS6502_Status_B    (1 << 4)
#define MOS6502_Status_V    (1 << 6)
#define MOS6502_Status_N    (1 << 7)

/**
 * @struct MOS6502_Status
 * @brief MOS6502 CPU Status register implementation.
 * @details Status register contains 7 status bits + 1 bit left unused.
 * The vast majority of instructions change Status Register state
 */
struct MOS6502_Status {
    union {
        struct {
            BYTE C: 1;             /**< Carry Flag */
            BYTE Z: 1;             /**< Zero Flag */
            BYTE I: 1;             /**< Interrupt Disable */
            BYTE D: 1;             /**< Decimal Mode */
            BYTE B: 1;             /**< Break Command */
            BYTE  : 1;             /**< Not Used */
            BYTE V: 1;             /**< Overflow Flag */
            BYTE N: 1;             /**< Negative Flag */
        };
        BYTE Value;
    };

    /**
     * @brief Update status register using given value.
     * @details Function updates Zero and Negative flags only because other flags need additional calculations.
     * @params value Input value to check.
     * @params mask Mask to define which bits to check.
     */
    FORCE_INLINE void UpdateStatusByValue(const BYTE &value, const BYTE mask) {
        if (mask & MOS6502_Status_Z)
            Z = (value == 0);
        if (mask & MOS6502_Status_N)
            N = (value & MOS6502_Status_N) > 0;
    }
};
