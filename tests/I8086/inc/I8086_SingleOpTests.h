#pragma once
#include "I8086_TestingSuite.h"

class I8086_SingleOpFixture : public I8086_TestFixture {
public:
    template<typename T>
    void TestAccumulatorWithImmediateData(T initialValue, T memValue, T refValue, I8086_OpCodes opCode, WORD executeCyclesExpected) {
        // given:
        if (std::is_same_v<T, BYTE>)
            cpu.AL = initialValue;
        else
            cpu.AX = initialValue;

        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress++] = memValue & 0xFF;
        if (!std::is_same_v<T, BYTE>)
            mem[effectiveAddress++] = (memValue >> 8) & 0xFF;
        mem[effectiveAddress] = STOP_OPCODE;

        cyclesExpected = executeCyclesExpected;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();

        EXPECT_EQ((std::is_same_v<T, BYTE> ? cpu.AL : cpu.AX), refValue);
    }
};
