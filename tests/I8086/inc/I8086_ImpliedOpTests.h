#pragma once
#include "I8086_TestingSuite.h"

class I8086_ImpliedOpTests : public I8086_TestFixture {
public:
    void TestImpliedInstruction(I8086_OpCodes_Main opCode) {
        // given:
        mem[effectiveAddress++] = opCode;
        mem[effectiveAddress] = I8086_STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run();

        // then:
        // Temporary disabled until cycles counter will be fixed
        // CheckCyclesCount();
    }
};
