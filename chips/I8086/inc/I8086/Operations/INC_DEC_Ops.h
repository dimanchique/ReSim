#pragma once

#include "I8086/I8086.h"

// Memory/Byte Register Inc/Dec GRP4/5

namespace INC_DEC {
    template<typename T>
    using CallbackSignature = T(I8086&, T);

    template<typename T>
    FORCE_INLINE void INC_DEC(I8086& cpu, const ModRegByte& modReg, CallbackSignature<T> *callback) {
        InstructionResult<T> instructionResult{};
        const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
        const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(opSize, InstructionDirection::MemReg_Imm, modReg);

        if (instructionData.leftOp.type == OperandType::Reg && std::is_same_v<T, WORD>)
            throw InvalidInstruction();

        const T operand = instructionData.singleOp.get(cpu, &instructionData.singleOp.operand);
        T opRes = callback(cpu, operand);
        instructionData.singleOp.set(cpu, &instructionData.singleOp.operand, opRes);
    }

    FORCE_INLINE void INC_DEC(I8086& cpu, const BYTE regIdx, CallbackSignature<WORD> *callback) {
        assert(regIdx <= 7);
        WORD* regPtr = cpu.GetRegWordPtr(regIdx);
        *regPtr = callback(cpu, *regPtr);
    }
}

template<typename T>
T PerformINC(I8086& cpu, T value) {
    T cached = value++;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    cpu.Status.O = cached > value; // 0xFFFF + 1 = 0x0000 ?
    // TODO: add Auxiliary Carry check
    return value;
}

template<typename T>
T PerformDEC(I8086& cpu, T value) {
    T cached = value--;

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    cpu.Status.O = cached < value; // 0x0000 - 1 = 0xFFFF ?
    // TODO: add Auxiliary Carry check
    return value;
}

template<typename T>
void INC_GRP4_Eb(I8086& cpu, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, modReg, &PerformINC);
}

template<typename T>
void DEC_GRP4_Eb(I8086& cpu, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, modReg, &PerformDEC);
}

template<typename T>
void INC_GRP5_Ev(I8086& cpu, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, modReg, &PerformINC);
}

template<typename T>
void DEC_GRP5_Ev(I8086& cpu, const ModRegByte& modReg) {
    INC_DEC::INC_DEC<T>(cpu, modReg, &PerformDEC);
}

// Word Register Inc/Dec 0x40 + Reg

void I8086_INC_WORD(const BYTE OpCode, I8086 &cpu) {
    INC_DEC::INC_DEC(cpu, OpCode - INC_AX, &PerformINC);
}

void I8086_INC_AX(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_CX(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_DX(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_BX(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_SP(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_BP(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_SI(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_INC_DI(BYTE OpCode, I8086 &cpu) {
    I8086_INC_WORD(OpCode, cpu);
}

void I8086_DEC_WORD(const BYTE OpCode, I8086 &cpu) {
    INC_DEC::INC_DEC(cpu, OpCode - DEC_AX, &PerformDEC);
}

void I8086_DEC_AX(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_CX(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_DX(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_BX(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_SP(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_BP(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_SI(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}

void I8086_DEC_DI(BYTE OpCode, I8086 &cpu) {
    I8086_DEC_WORD(OpCode, cpu);
}
