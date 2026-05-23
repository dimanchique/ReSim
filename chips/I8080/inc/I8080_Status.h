#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

#define I8080_Status_C          (1 << 0)
#define I8080_Status_P          (1 << 2)
#define I8080_Status_AC         (1 << 4)
#define I8080_Status_Z          (1 << 6)
#define I8080_Status_S          (1 << 7)

/**
 * @struct I8080_Status
 * @brief I8080 CPU Status register implementation.
 * @details Status register contains 5 status bits + 3 bit left unused.
 * The vast majority of instructions change Status Register state
 */
struct I8080_Status {
    union {
        struct {
            BYTE C : 1;             /**< Carry Flag */
            BYTE   : 1;             /**< Not Used */
            BYTE P : 1;             /**< Parity Flag */
            BYTE   : 1;             /**< Not Used */
            BYTE AC: 1;             /**< Auxiliary Carry Flag */
            BYTE   : 1;             /**< Not Used */
            BYTE Z : 1;             /**< Zero Flag */
            BYTE S : 1;             /**< Sign Flag */
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
        if (mask & I8080_Status_Z)
            Z = (value == 0);
        if (mask & I8080_Status_S)
            S = (value & I8080_Status_S) > 0;
        if (mask & I8080_Status_P) {
            BYTE bitCount = 0;
            for (BYTE idx = 0; idx < 8; ++idx) {
                if ((value >> idx) & 0x1)
                    bitCount++;
            }
            P = ~(bitCount & 0x1);
        }
    }

    /**
     * @brief Update Auxiliary Carry flag using short half adder logic.
     * @details Half adder logic is executing until fourth bit value is checked.
     * @params firstOp First operand of add operation.
     * @params secondOpWithCarry Second operand of add operation.
     * @params initialCarry Optional initial carry (for ADC/SBB instructions).
     */
    FORCE_INLINE void
    SetAuxiliaryCarryFlag(const BYTE firstOp, const BYTE secondOpWithCarry, const BYTE initialCarry = 0) {
        BYTE carryFlag = initialCarry;
        BYTE firstOpArg, secondOpArg;
        for (BYTE idx = 0; idx < 4; ++idx) {
            firstOpArg = (firstOp >> idx) & 0x01;
            secondOpArg = (secondOpWithCarry >> idx) & 0x01; // Consider the carry in the second operand
            carryFlag = ((firstOpArg + secondOpArg + carryFlag) >> 1) & 0x01;
        }
        AC = carryFlag;
    }
};
