#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Jump
 * @addressing Absolute
 * @details Sets the program counter to the address specified by the operand.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_JMP_ABS(MOS6502 &cpu) {
    cpu.PC = cpu.FetchWord();
}

/**
 * @brief Jump
 * @addressing Indirect
 * @details Sets the program counter to the address specified by the operand.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_JMP_IND(MOS6502 &cpu) {
    const WORD targetAddress = cpu.FetchWord();
    cpu.PC = cpu.ReadWord(targetAddress);
}

/**
 * @brief Jump to Subroutine
 * @addressing Absolute
 * @details The JSR instruction pushes the address (minus one) of the return point on to the stack
 * and sets the program counter to the target memory address.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_JSR_ABS(MOS6502 &cpu) {
    const WORD targetAddress = cpu.FetchWord();
    cpu.PushProgramCounterToStack();
    cpu.PC = targetAddress;
    cpu.cycles++;
}

/**
 * @brief Return from Subroutine
 * @addressing Implied
 * @details The RTS instruction is used at the end of a subroutine to return to the calling routine.
 * It pulls the program counter (minus one) from the stack.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_RTS_IMPL(MOS6502 &cpu) {
    cpu.PC = cpu.PopAddressFromStack();
    cpu.cycles++;
}

/**
 * @brief Force Interrupt
 * @addressing Implied
 * @details The BRK instruction forces the generation of an interrupt request.
 * The program counter and processor status are pushed on the stack
 * then the IRQ interrupt vector at $FFFE/FFFF is loaded into the PC and the break flag in the status set to one.
 * @todo fix cycles count mismatch
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_BRK_IMPL(MOS6502 &cpu) {
    cpu.PushProgramCounterToStack();
    cpu.PushStatusToStack();
    cpu.PC = cpu.ReadWord(0xFFFE);
    cpu.Status.B = true;
    cpu.cycles--; // temporary fix extra cycle
}

/**
 * @brief Return from Interrupt
 * @addressing Implied
 * @details The RTI instruction is used at the end of an interrupt processing routine.
 * It pulls the processor flags from the stack followed by the program counter.
 * @todo fix cycles count mismatch
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_RTI_IMPL(MOS6502 &cpu) {
    cpu.PopStatusFromStack();
    cpu.PC = cpu.PopAddressFromStack();
    cpu.Status.B = false;
    cpu.cycles--; // temporary fix extra cycle
}
