#pragma once

#include "I8086/I8086.h"

namespace NOT_NEG {
    template<typename T>
    using CallbackSignature = T(I8086&, T);

    template<typename T>
    FORCE_INLINE void NOT_NEG(I8086& cpu, const ModRegByte& modReg, CallbackSignature<T> *callback) {
        InstructionResult<T> instructionResult{};
        const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
        const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(opSize, InstructionDirection::MemReg_Imm, modReg);

        const T operand = instructionData.singleOp.get(cpu, &instructionData.singleOp.operand);
        T opRes = callback(cpu, operand);
        instructionData.singleOp.set(cpu, &instructionData.singleOp.operand, opRes);
    }
}

template<typename T>
T PerformNEG(I8086& cpu, T value) {
    T cached = value;
    value = -value;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    cpu.Status.C = (cached != 0);
    // TODO: add Overflow and Auxiliary Carry check
    return value;
}

template<typename T>
T PerformNOT(I8086& cpu, T value) {
    value = ~value;
    return value;
}

template<typename T>
void I8086_NEG(I8086& cpu, const ModRegByte& modReg) {
    NOT_NEG::NOT_NEG<T>(cpu, modReg, &PerformNEG);
}

template<typename T>
void I8086_NOT(I8086& cpu, const ModRegByte& modReg) {
    NOT_NEG::NOT_NEG<T>(cpu, modReg, &PerformNOT);
}
