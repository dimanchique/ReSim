#include "I8080_TestingSuite.h"

class I8080_XTHLFixture : public I8080_TestFixture {
public:
    void XTHL_CanExchangeValues(const WORD stackPointerAddress, const WORD stackPointerValue, const WORD registerValueH) {
        // given:
        cpu.SP = stackPointerAddress;
        I8080::wordToRegisterSwapped(stackPointerValue, mem[cpu.SP], mem[cpu.SP + 1]);
        I8080::wordToRegisterSwapped(registerValueH, cpu.H, cpu.L);
        mem[0x0000] = I8080_OpCodes::XTHL;

        cyclesExpected = 16;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:

        const WORD swappedValueH = I8080::wordRegisterAsWordUnswapped(cpu.H);
        const WORD swappedValueStackPointer = I8080::wordRegisterAsWordUnswapped(mem[cpu.SP]);
        EXPECT_NE(swappedValueStackPointer, stackPointerValue);
        EXPECT_NE(swappedValueH, registerValueH);
        EXPECT_EQ(swappedValueStackPointer, registerValueH);
        EXPECT_EQ(swappedValueH, stackPointerValue);
        CheckCyclesCount();
    }
};

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_1) {
    XTHL_CanExchangeValues(0xFFFD, 0x1234, 0x2345);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_2) {
    XTHL_CanExchangeValues(0xFFDD, 0xABBA, 0xFF00);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_3) {
    XTHL_CanExchangeValues(0xFFD0, 0xAADD, 0xDEAD);
}

TEST_F(I8080_XTHLFixture, XTHL_CanExchangeValues_4) {
    XTHL_CanExchangeValues(0x10AD, 0xF00D, 0x0B3C);
}
