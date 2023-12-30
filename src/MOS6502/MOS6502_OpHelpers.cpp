#include <MOS6502_OpHelpers.h>
#include "Operations/MOS6502_JMP_JSR_RTS_RTI_Ops.h"
#include <Operations/MOS6502_LDA_Ops.h>
#include <Operations/MOS6502_LDX_Ops.h>
#include <Operations/MOS6502_LDY_Ops.h>
#include <Operations/MOS6502_STA_Ops.h>
#include <Operations/MOS6502_STX_Ops.h>
#include <Operations/MOS6502_STY_Ops.h>
#include "Operations/MOS6502_CL_Ops.h"
#include "Operations/MOS6502_SE_Ops.h"
#include "Operations/MOS6502_DEC_Ops.h"
#include "Operations/MOS6502_INC_Ops.h"
#include "Operations/MOS6502_T_Ops.h"
#include "Operations/MOS6502_P_Ops.h"
#include "Operations/MOS6502_AND_Ops.h"
#include "Operations/MOS6502_ORA_Ops.h"
#include "Operations/MOS6502_EOR_Ops.h"
#include "Operations/MOS6502_ASL_Ops.h"
#include "Operations/MOS6502_LSR_Ops.h"
#include "Operations/MOS6502_BIT_Ops.h"
#include "Operations/MOS6502_ROL_Ops.h"
#include "Operations/MOS6502_ROR_Ops.h"
#include "Operations/MOS6502_NOP_Op.h"
#include "Operations/MOS6502_B_Ops.h"
#include "Operations/MOS6502_CMP_Ops.h"
#include "Operations/MOS6502_CPX_Ops.h"
#include "Operations/MOS6502_CPY_Ops.h"
#include "Operations/MOS6502_ADC_Ops.h"
#include "Operations/MOS6502_SBC_Ops.h"

static void MOS6502_INVALID_OP(Memory &memory, MOS6502 &cpu) {}

using OpSignature = void (*)(Memory &, MOS6502 &);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) MOS6502_##call
#include "MOS6502_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeCommand(const BYTE opcode, Memory &memory, MOS6502 &cpu) {
    if(opcode == 0xFF)
        return false;
    const auto &Instruction = Ops[opcode];
    Instruction(memory, cpu);
    return Instruction != MOS6502_INVALID_OP;
}
