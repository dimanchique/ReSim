#pragma once

#include "I8086/I8086.h"

template<typename T>
using InstructionCallback = void(InstructionResult<T> &);

template<typename T>
using StatusCallback = void(I8086 &, const InstructionResult<T> &);

// Generic version of execution default instruction
// Works with Ex,Gx/Gx,Ex instructions
// Result will be stored in left operand on instruction
template<typename T>
FORCE_INLINE void I8086_EGx_EGx(I8086 &cpu,
                                InstructionCallback<T> *callback,
                                StatusCallback<T> *statusCallback,
                                const InstructionDirection instructionDirection,
                                const OperandDirection operandDirection) {
    InstructionResult<T> instructionResult{};
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionData<T>(opSize, instructionDirection);

    const T leftOp = instructionData.leftOp.get(cpu, &instructionData.leftOp.operand);
    const T rightOp = instructionData.rightOp.get(cpu, &instructionData.rightOp.operand);

    instructionResult.leftOp.before = leftOp;
    instructionResult.rightOp.before = rightOp;

    callback(instructionResult);

    if (operandDirection & OperandDirection::RightToLeft)
        instructionData.leftOp.set(cpu, &instructionData.leftOp.operand, instructionResult.leftOp.after);
    if (operandDirection & OperandDirection::LeftToRight)
        instructionData.rightOp.set(cpu, &instructionData.rightOp.operand, instructionResult.rightOp.after);

    if (statusCallback)
        statusCallback(cpu, instructionResult);
}

template<typename T>
FORCE_INLINE void I8086_Ex_Ix(I8086 &cpu,
                              const ModRegByte modRegByte,
                              InstructionCallback<T> *callback,
                              StatusCallback<T> *statusCallback) {
    InstructionResult<T> instructionResult{};
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(opSize, InstructionDirection::MemReg_Imm, modRegByte);

    const T immValue = cpu.Fetch<T>();
    const T op = instructionData.singleOp.get(cpu, &instructionData.singleOp.operand);

    instructionResult.leftOp.before = op;
    instructionResult.rightOp.before = immValue;

    callback(instructionResult);

    instructionData.singleOp.set(cpu, &instructionData.singleOp.operand, instructionResult.leftOp.after);

    if (statusCallback)
        statusCallback(cpu, instructionResult);
}
