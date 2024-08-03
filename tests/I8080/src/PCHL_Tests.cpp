#include "I8080_TestingSuite.h"

class I8080_PCHLFixture : public I8080_TestFixture {
public:
    void PCHL_CanLoadPC(const BYTE lsbAddr, const BYTE msbAddr) {
        // given:
        cpu.H = lsbAddr;
        cpu.L = msbAddr;
        const WORD targetAddr = ReSimFunctionLibrary::ContentManipulation::getWordAsSwappedBytes_Copy(cpu.H, cpu.L);
        mem[0x0000] = I8080_OpCodes::PCHL;

        cyclesExpected = 5;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, targetAddr);
        CheckCyclesCount();
    }
};

TEST_F(I8080_PCHLFixture, PCHL_CanLoadPC_1) {
    PCHL_CanLoadPC(0xDE, 0xAD);
}

TEST_F(I8080_PCHLFixture, PCHL_CanLoadPC_2) {
    PCHL_CanLoadPC(0xAB, 0xBA);
}

TEST_F(I8080_PCHLFixture, PCHL_CanLoadPC_3) {
    PCHL_CanLoadPC(0x0A, 0x55);
}

