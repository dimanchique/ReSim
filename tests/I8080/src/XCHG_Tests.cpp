#include "I8080_TestingSuite.h"

class I8080_XCHGFixture : public I8080_TestFixture {
public:
    void XCHG_CanExchangeValues(const WORD initialValueD, const WORD initialValueH) {
        // given:
        I8080::wordToRegisterSwapped(initialValueD, cpu.D, cpu.E);
        I8080::wordToRegisterSwapped(initialValueH, cpu.H, cpu.L);
        mem[0x0000] = I8080_OpCodes::XCHG;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        const WORD swappedValueD = I8080::wordRegisterAsWordSwapped(cpu.D, cpu.E);
        const WORD swappedValueH = I8080::wordRegisterAsWordSwapped(cpu.H, cpu.L);
        EXPECT_NE(swappedValueD, initialValueD);
        EXPECT_NE(swappedValueH, initialValueH);
        EXPECT_EQ(initialValueD, swappedValueH);
        EXPECT_EQ(initialValueH, swappedValueD);
        CheckCyclesCount();
    }
};

TEST_F(I8080_XCHGFixture, XCHG_CanExchangeValues_1) {
    XCHG_CanExchangeValues(0x1234, 0x2345);
}

TEST_F(I8080_XCHGFixture, XCHG_CanExchangeValues_2) {
    XCHG_CanExchangeValues(0x00AA, 0x00FF);
}

TEST_F(I8080_XCHGFixture, XCHG_CanExchangeValues_3) {
    XCHG_CanExchangeValues(0xDDAA, 0xCCFF);
}

TEST_F(I8080_XCHGFixture, XCHG_CanExchangeValues_4) {
    XCHG_CanExchangeValues(0x3355, 0x00FF);
}
