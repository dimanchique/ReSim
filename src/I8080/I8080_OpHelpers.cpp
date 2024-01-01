#include "I8080.h"
#include "Operations/I8080_ADD_Ops.h"
#include "Operations/I8080_ANA_Ops.h"
#include "Operations/I8080_ROT_Ops.h"
#include "Operations/I8080_LDA_Ops.h"
#include "Operations/I8080_NOP_Ops.h"
#include "Operations/I8080_MOV_A_Ops.h"
#include "Operations/I8080_MOV_B_Ops.h"
#include "Operations/I8080_MOV_C_Ops.h"
#include "Operations/I8080_MOV_D_Ops.h"
#include "Operations/I8080_MOV_E_Ops.h"
#include "Operations/I8080_MOV_H_Ops.h"
#include "Operations/I8080_MOV_L_Ops.h"
#include "Operations/I8080_MOV_M_Ops.h"

static void I8080_INVALID_OP(Memory &memory, I8080 &cpu) {}

using OpSignature = void (*)(Memory &, I8080 &);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8080_##call
#include "I8080_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeCommand(const BYTE opcode, Memory &memory, I8080 &cpu) {
    if(opcode == 0xFF)
        return false;
    const auto &Instruction = Ops[opcode];
    Instruction(memory, cpu);
    return Instruction != I8080_INVALID_OP;
}
