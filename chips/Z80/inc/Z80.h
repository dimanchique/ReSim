#pragma once

#include "compute.h"
#include "core/macro.h"
#include "Z80_Status.h"

#define Z80_STOP_OPCODE Z80_OpCodes_Main::HALT /**< HALT instruction opcode used to stop execution of finite programs */

/**
 * @class Z80
 * @brief Zilog Z80 CPU implementation
 * @details Z80 (Launch: 1976) is an 8-bit microprocessor with 158 supported instructions and 10 addressing modes.
 * Registers:
 * - Program Counter register (PC)
 * - Stack Pointer register (SP)
 * - Accumulator register (A and A')
 * - BC paired register (BC and BC')
 * - DE paired register (DE and DE')
 * - HL paired register (HL and HL')
 * - X index register (X)
 * - Y index register (Y)
 * - Interrupt Vector and Refresh Counter I/R paired register
 * - Status register (F and F')
 * - 4 bits register for interrupt status and interrupt mode
 * Max CPU clock rate 2.5-8 MHz. Data width: 8 bits. Address width: 16 bits
 */
class Z80 final: public Compute<WORD> {

    void Reset() noexcept override;

    U32 Run() override;

    bool Step() override;

};
