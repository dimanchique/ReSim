#pragma once

#include "I8086.h"

namespace ROL_RCL_SAL_SHL {
    template<typename T>
    using CallbackSignature = T(I8086 &, T, const BYTE *);

    template<typename T>
    FORCE_INLINE void RXL_ByX(I8086 &cpu, const ModRegByte &modReg, CallbackSignature<T> *callback, BYTE *countPtr = nullptr) {
        InstructionResult<T> instructionResult{};
        const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
        const InstructionData instructionData = cpu.GetInstructionDataNoFetch<T>(opSize, InstructionDirection::MemReg_Imm, modReg);

        const T operand = instructionData.singleOp.get(cpu);
        T opRes = callback(cpu, operand, countPtr);
        instructionData.singleOp.set(cpu, opRes);
    }
}

template<typename T>
T PerformROL(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;

    do {
        cpu.Status.C = (value >> highOrderBitPosition) & 0x01;
        value <<= 1;
        value += cpu.Status.C;
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = ((value >> highOrderBitPosition) & 0x01) != (value & 0x01);

    return value;
}

template<typename T>
T PerformRCL(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;
    BYTE tmpCarry = 0;

    do {
        tmpCarry = cpu.Status.C;
        cpu.Status.C = (value >> highOrderBitPosition) & 0x01;
        value <<= 1;
        value += tmpCarry;
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = ((value >> highOrderBitPosition) & 0x01) != (value & 0x01);

    return value;
}

template<typename T>
T PerformSAL_SHL(I8086& cpu, T value, const BYTE* countPtr = nullptr) {
    BYTE highOrderBitPosition = (sizeof(value) * 8) - 1;
    BYTE count = countPtr ? *countPtr : 1;

    do {
        cpu.Status.C = (value >> highOrderBitPosition) & 0x01;
        value <<= 1;
        count--;
    } while (count > 0);

    if (!countPtr)
        cpu.Status.O = ((value >> highOrderBitPosition) & 0x01) != (value & 0x01);

    cpu.Status.UpdateStatusByValue<T>(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
    return value;
}

template<typename T>
void ROL_ByOne(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformROL);
}

template<typename T>
void ROL_ByCL(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformROL, &cpu.CL);
}

template<typename T>
void RCL_ByOne(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformRCL);
}

template<typename T>
void RCL_ByCL(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformRCL, &cpu.CL);
}

template<typename T>
void SAL_SHL_ByOne(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformSAL_SHL);
}

template<typename T>
void SAL_SHL_ByCL(I8086& cpu, const ModRegByte& modReg) {
    ROL_RCL_SAL_SHL::RXL_ByX<T>(cpu, modReg, &PerformSAL_SHL, &cpu.CL);
}
