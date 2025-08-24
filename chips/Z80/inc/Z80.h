#pragma once

#include "Z80_Status.h"
#include "compute.h"
#include "core/macro.h"
#include "compute.h"
#include "memory.h"
#include "function_library/data_manipulation.h"

#define STOP_OPCODE Z80_OpCodes_Main::HALT /**< HALT instruction opcode used to stop execution of finite programs */

class Z80 final: public Compute {
};
