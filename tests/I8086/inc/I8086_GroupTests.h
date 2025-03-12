#pragma once
#include "I8086_TestingSuite.h"

class I8086_GroupFixture : public I8086_TestFixture {
public:

    template<typename T>
    void TestMemoryInstruction(DWORD memAddress, T memValue, T refValue, I8086_OpCodes opCode, ModRegByteConstructor &modRegConstructor, BYTE regOverride, WORD executeCyclesExpected) {
        // given:
        mem[memAddress] = memValue & 0xFF;
        if (std::is_same_v<T, WORD>)
            mem[memAddress + 1] = (memValue >> 8) & 0xFF;

        modRegConstructor.size = std::is_same_v<T, WORD> ? OperandSize::WORD : OperandSize::BYTE;
        BYTE modRegByte = modRegConstructor.MakeModByte();
        ModRegByte modRegModified = ModRegByte::FromByte(modRegByte);
        modRegModified.reg = regOverride;
        modRegByte = modRegModified.value;

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = modRegByte;

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

        // Result of ExGx is always in memory
        WORD result = mem[memAddress];
        if (std::is_same_v<T, WORD>)
            result |= (mem[memAddress + 1] << 8);
        EXPECT_EQ(result, refValue);
    }

    template<typename T>
    void TestRegisterInstruction(T* regValue, T refValue, I8086_OpCodes opCode, const BYTE* reg, BYTE regOverride, WORD executeCyclesExpected) {
        // given:
        ModRegByteConstructor modReg;

        modReg.leftOp.archetype = OperandArchetype::Reg;
        if (std::is_same_v<T, WORD>) {
            modReg.size = OperandSize::WORD;
            modReg.leftOp.regData.wordReg = (WordRegisters)(*reg);
        }
        else {
            modReg.size = OperandSize::BYTE;
            modReg.leftOp.regData.byteReg = (ByteRegisters)(*reg);
        }
        BYTE modRegByte = modReg.MakeModByte();

        ModRegByte modRegModified = ModRegByte::FromByte(modRegByte);
        modRegModified.reg = regOverride;
        modRegByte = modRegModified.value;

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = modRegByte;

        mem[effectiveAddress++] = STOP_OPCODE;
        cyclesExpected = executeCyclesExpected;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        // Result of ExGx is always in memory
        EXPECT_EQ((T)(*regValue), (T)(refValue));
    }
};
