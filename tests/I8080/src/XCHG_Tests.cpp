#include "I8080_TestingSuite.h"

class I8080_XCHGFixture : public I8080_TestFixture {
public:
    void XCHG_CanExchangeValues(const WORD initialValueD, const WORD initialValueH) {
        // given:
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(initialValueD, cpu.D, cpu.E);
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(initialValueH, cpu.H, cpu.L);
        mem[0x0000] = XCHG;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        const WORD swappedValueD = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.D, cpu.E);
        const WORD swappedValueH = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
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
