#include "Z80.h"
#include "Z80_OpCodes_Main.h"
#include "Z80_OpGroupsHelpers.h"

static void Z80_INVALID_OP(Z80&) {}

using OpSignature = void (*)(Z80&);

/** Bit Instructions lookup table */
constexpr static OpSignature Bit_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_Bit.h"
#undef ADD_CALL
#endif
        };

void Z80_Bit_Group(Z80& cpu) {
    // fetch and use callback from Bit Group matrix
}

/** IX Instructions lookup table */
constexpr static OpSignature IX_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_IX.h"
#undef ADD_CALL
#endif
        };

void Z80_IX_Group(Z80& cpu) {
    // fetch and use callback from IX Group matrix
}

/** IX Bit Instructions lookup table */
constexpr static OpSignature IX_Bit_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_IX_Bit.h"
#undef ADD_CALL
#endif
        };

void Z80_IX_Bit_Group(Z80& cpu) {
    // fetch and use callback from IX Bit Group matrix
}

/** Misc Instructions lookup table */
constexpr static OpSignature Misc_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_Misc.h"
#undef ADD_CALL
#endif
        };

void Z80_Misc_Group(Z80& cpu) {
    // fetch and use callback from Misc Group matrix
}

/** IY Instructions lookup table */
constexpr static OpSignature IY_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_IY.h"
#undef ADD_CALL
#endif
        };

void Z80_IY_Group(Z80& cpu) {
    // fetch and use callback from IY Group matrix
}

/** IY Bit Instructions lookup table */
constexpr static OpSignature IY_Bit_Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_IY_Bit.h"
#undef ADD_CALL
#endif
        };

void Z80_IY_Bit_Group(Z80& cpu) {
    // fetch and use callback from IY Bit Group matrix
}
