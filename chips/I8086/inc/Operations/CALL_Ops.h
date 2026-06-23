#pragma once

#include "I8086.h"

void I8086_CALL_Ap(BYTE, I8086 &cpu) {
    const WORD offset = cpu.Fetch<WORD>();
    const WORD segmentBase = cpu.Fetch<WORD>();

    cpu.PushDataToStack(cpu.CS);
    cpu.PushDataToStack(cpu.PC);

    cpu.PC = offset;
    cpu.CS = segmentBase;
}

void I8086_CALL_Jv(BYTE, I8086 &cpu) {
    const WORD displacement = cpu.Fetch<WORD>();

    cpu.PushDataToStack(cpu.PC);

    cpu.PC += displacement;
}

void CALL_GRP5(I8086& cpu, const ModRegByte& modReg) {
    const OperandSize opSize = OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(opSize, InstructionDirection::MemReg_Imm, modReg);
    WORD newPC = instructionData.leftOp.get(cpu);

    cpu.PushDataToStack(cpu.PC);

    cpu.PC = newPC;
}

void CALL_GRP5_MP(I8086& cpu, const ModRegByte& modReg) {
    const OperandSize opSize = OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(opSize, InstructionDirection::MemReg_Imm, modReg);
    DWORD effectiveAddress = instructionData.leftOp.operand.mem;
    WORD newPC = cpu.Read<WORD>(effectiveAddress);
    WORD newCS = cpu.Read<WORD>(effectiveAddress + 2);

    cpu.PushDataToStack(cpu.CS);
    cpu.PushDataToStack(cpu.PC);

    cpu.CS = newCS;
    cpu.PC = newPC;
}
