#include "I8080_TestingSuite.h"

class I8080_XTHLFixture : public I8080_TestFixture {
public:
    void XTHL_CanExchangeValues(const WORD stackPointerAddress, const WORD stackPointerValue, const WORD registerValueH) {
        // given:
        cpu.SP = stackPointerAddress;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(stackPointerValue, mem[cpu.SP], mem[cpu.SP + 1]);
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(registerValueH, cpu.H, cpu.L);
        mem[0x0000] = XTHL;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 18;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:

        const WORD swappedValueH = cpu.HL;
        const WORD swappedValueStackPointer = *reinterpret_cast<WORD*>(&mem[cpu.SP]);
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
