#pragma once

#include "I8086.h"

template<typename T>
using InstructionCallback = void(I8086 &, InstructionResult<T> &);

// Generic version of execution default instruction
// Works with Ex,Gx/Gx,Ex instructions
// Result will be stored in left operand on instruction
template<typename T>
FORCE_INLINE void I8086_EGx_EGx(I8086 &cpu,
                                InstructionCallback<T> *callback,
                                const InstructionDirection instructionDirection,
                                const OperandDirection operandDirection,
                                const bool shouldStoreResult = true) {
    InstructionResult<T> instructionResult;
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionData<T>(opSize, instructionDirection);

    const T leftOp = instructionData.leftOp.get(cpu);
    const T rightOp = instructionData.rightOp.get(cpu);

    instructionResult.leftOp.before = leftOp;
    instructionResult.rightOp.before = rightOp;

    callback(cpu, instructionResult);

    if (shouldStoreResult) {
        if (operandDirection & OperandDirection::RightToLeft)
            instructionData.leftOp.set(cpu, instructionResult.leftOp.after);
        if (operandDirection & OperandDirection::LeftToRight)
            instructionData.rightOp.set(cpu, instructionResult.rightOp.after);
    }
}

template<typename T>
FORCE_INLINE void I8086_Ex_Ix(I8086 &cpu,
                              const ModRegByte modRegByte,
                              InstructionCallback<T> *callback,
                              const bool shouldStoreResult = true) {
    InstructionResult<T> instructionResult;
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(opSize, InstructionDirection::MemReg_Imm, modRegByte);

    const T immValue = cpu.Fetch<T>();
    const T op = instructionData.leftOp.get(cpu);

    instructionResult.leftOp.before = op;
    instructionResult.rightOp.before = immValue;

    callback(cpu, instructionResult);

    if (shouldStoreResult)
        instructionData.leftOp.set(cpu, instructionResult.leftOp.after);
}
