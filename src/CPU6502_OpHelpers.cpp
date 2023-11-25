#include <CPU6502_OpHelpers.h>
#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include <Operations/CPU6502_LDA_Ops.h>
#include <Operations/CPU6502_LDX_Ops.h>
#include <Operations/CPU6502_LDY_Ops.h>
#include <Operations/CPU6502_STA_Ops.h>
#include <Operations/CPU6502_STX_Ops.h>
#include <Operations/CPU6502_STY_Ops.h>
#include "Operations/CPU6502_CL_Ops.h"
#include "Operations/CPU6502_SE_Ops.h"
#include "Operations/CPU6502_DEC_Ops.h"
#include "Operations/CPU6502_INC_Ops.h"
#include "Operations/CPU6502_T_Ops.h"
#include "Operations/CPU6502_P_Ops.h"
#include "Operations/CPU6502_AND_Ops.h"
#include "Operations/CPU6502_ORA_Ops.h"
#include "Operations/CPU6502_EOR_Ops.h"
#include "Operations/CPU6502_ASL_Ops.h"
#include "Operations/CPU6502_LSR_Ops.h"
#include "Operations/CPU6502_BIT_Ops.h"
#include "Operations/CPU6502_ROL_Ops.h"
#include "Operations/CPU6502_ROR_Ops.h"
#include "Operations/CPU6502_NOP_Op.h"
#include "Operations/CPU6502_B_Ops.h"
#include "Operations/CPU6502_CMP_Ops.h"
#include "Operations/CPU6502_CPX_Ops.h"
#include "Operations/CPU6502_CPY_Ops.h"
#include "Operations/CPU6502_ADC_Ops.h"
#include "Operations/CPU6502_SBC_Ops.h"

static void CPU6502_FAKE_NOP(Memory &memory, CPU6502 &cpu) {}

using OpSignature = void (*)(Memory &, CPU6502 &);

/** Instructions table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) CPU6502_##call
#include "CPU6502_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeCommand(const BYTE opcode, Memory &memory, CPU6502 &cpu) {
    if(opcode == 0xFF)
        return false;
    const auto &Instruction = Ops[opcode];
    Instruction(memory, cpu);
    return Instruction != CPU6502_FAKE_NOP;
}
