#pragma once
#include "I8086_TestingSuite.h"

class I8086_DoubleOpFixture : public I8086_TestFixture {
public:

    template<typename T>
    void TestMemRegInstruction(DWORD memAddress, T memValue, I8086_OpCodes opCode, ModRegByteConstructor &modRegConstructor, WORD executeCyclesExpected) {
        // given:
        mem[memAddress] = memValue & 0xFF;
        if (std::is_same_v<T, WORD>)
            mem[memAddress + 1] = (memValue >> 8) & 0xFF;

        modRegConstructor.size = std::is_same_v<T, WORD> ? OperandSize::WORD : OperandSize::BYTE;

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = modRegConstructor.MakeModByte();

        if (modRegConstructor.leftOp.memData.mode == modeDirect) {
            mem[effectiveAddress++] = memAddress & 0xFF;
            mem[effectiveAddress++] = (memAddress >> 8) & 0xFF;
        }

        if (modRegConstructor.leftOp.memData.dispSize > 0) {
            mem[effectiveAddress++] = modRegConstructor.leftOp.memData.dispValue & 0xFF;
            if (modRegConstructor.leftOp.memData.dispSize > 1)
                mem[effectiveAddress++] = (modRegConstructor.leftOp.memData.dispValue >> 8) & 0xFF;
        }

        mem[effectiveAddress++] = STOP_OPCODE;
        cyclesExpected = executeCyclesExpected;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();
    }

    template<typename T>
    void TestRegRegInstruction(const BYTE *leftReg, const BYTE *rightReg, I8086_OpCodes opCode, WORD executeCyclesExpected) {
        // given:
        ModRegByteConstructor modReg;

        if (std::is_same_v<T, WORD>)
            modReg.size = OperandSize::WORD;
        else
            modReg.size = OperandSize::BYTE;

        modReg.leftOp.archetype = OperandArchetype::Reg;
        if (std::is_same_v<T, WORD>)
            modReg.leftOp.regData.wordReg = (WordRegisters)(*leftReg);
        else
            modReg.leftOp.regData.byteReg = (ByteRegisters)(*leftReg);

        modReg.rightOp.archetype = OperandArchetype::Reg;
        if (std::is_same_v<T, WORD>)
            modReg.rightOp.regData.wordReg = (WordRegisters)(*rightReg);
        else
            modReg.rightOp.regData.byteReg = (ByteRegisters)(*rightReg);

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = modReg.MakeModByte();

        mem[effectiveAddress++] = STOP_OPCODE;
        cyclesExpected = executeCyclesExpected;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();
    }
};
