#include "I8080_TestingSuite.h"

class I8080_RST_Fixture : public I8080_TestFixture {
public:
    void RST_CanReset(const I8080_OpCodes resetVectorOpCode, const BYTE address) {
        // given:
        cpu.PC = 0x1000;
        mem[0x1000] = resetVectorOpCode;
        cyclesExpected = 11;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.PC, (WORD)(address << 3));
        CheckCyclesCount();
    }
};

TEST_F(I8080_RST_Fixture, RST_CanReset0) {
    RST_CanReset(I8080_OpCodes::RST_0, 0b000);
}

TEST_F(I8080_RST_Fixture, RST_CanReset1) {
    RST_CanReset(I8080_OpCodes::RST_1, 0b001);
}

TEST_F(I8080_RST_Fixture, RST_CanReset2) {
    RST_CanReset(I8080_OpCodes::RST_2, 0b010);
}

TEST_F(I8080_RST_Fixture, RST_CanReset3) {
    RST_CanReset(I8080_OpCodes::RST_3, 0b011);
}

TEST_F(I8080_RST_Fixture, RST_CanReset4) {
    RST_CanReset(I8080_OpCodes::RST_4, 0b100);
}

TEST_F(I8080_RST_Fixture, RST_CanReset5) {
    RST_CanReset(I8080_OpCodes::RST_5, 0b101);
}

TEST_F(I8080_RST_Fixture, RST_CanReset6) {
    RST_CanReset(I8080_OpCodes::RST_6, 0b110);
}

TEST_F(I8080_RST_Fixture, RST_CanReset7) {
    RST_CanReset(I8080_OpCodes::RST_7, 0b111);
}
