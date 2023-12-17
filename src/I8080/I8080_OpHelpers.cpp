#include "I8080/I8080.h"

static void I8080_FAKE_NOP(Memory &memory, I8080 &cpu) {}

using OpSignature = void (*)(Memory &, I8080 &);

/** Instructions table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8080_##call

#undef ADD_CALL
#endif
        };

bool DecodeCommand(const BYTE opcode, Memory &memory, I8080 &cpu) {
    if(opcode == 0xFF)
        return false;
    const auto &Instruction = Ops[opcode];
    Instruction(memory, cpu);
    return Instruction != I8080_FAKE_NOP;
}
