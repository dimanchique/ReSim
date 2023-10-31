#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Jump – Absolute
 * @details Sets the program counter to the address specified by the operand.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_JMP_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Jump – Indirect
 * @details Sets the program counter to the address specified by the operand.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_JMP_IND(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Jump to Subroutine – Absolute
 * @details The JSR instruction pushes the address (minus one) of the return point on to the stack
 * and then sets the program counter to the target memory address.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_JSR_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Return from Subroutine – Implied
 * @details The RTS instruction is used at the end of a subroutine to return to the calling routine.
 * It pulls the program counter (minus one) from the stack.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_RTS_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Force Interrupt – Implied
 * @details The BRK instruction forces the generation of an interrupt request.
 * The program counter and processor status are pushed on the stack
 * then the IRQ interrupt vector at $FFFE/F is loaded into the PC and the break flag in the status set to one.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_BRK_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Return from Interrupt – Implied
 * @details The RTI instruction is used at the end of an interrupt processing routine.
 * It pulls the processor flags from the stack followed by the program counter.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_RTI_IMPL(Memory &memory, CPU6502 &cpu);
