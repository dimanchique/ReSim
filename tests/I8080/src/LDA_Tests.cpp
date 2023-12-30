#include "I8080_TestingSuite.h"

class I8080_LDAFixture : public I8080_TestFixture {
public:
    void LDA_CanLoadValue(I8080_OpCodes opcode, BYTE memoryValue, WORD memoryAddress) {
        // given:
        mem[0x0000] = opcode;
        mem[0x0001] = memoryAddress & 0xFF;
        mem[0x0002] = (memoryAddress >> 8) & 0xFF;
        mem[memoryAddress] = memoryValue;

        cyclesExpected = 13;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue);
        CheckCyclesCount();
    }

    void LDAX_CanLoadValue(I8080_OpCodes opcode, BYTE memoryValue, BiRegister &targetRegister, WORD memoryAddress) {
        // given:
        targetRegister = memoryAddress;
        mem[0x0000] = opcode;
        mem[memoryAddress] = memoryValue;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, memoryValue);
        CheckCyclesCount();
    }
};

TEST_F(I8080_LDAFixture, LDA_CanLoadValue_1) {
    LDA_CanLoadValue(I8080_OpCodes::LDA, 0x25, 0x1234);
}

TEST_F(I8080_LDAFixture, LDA_CanLoadValue_2) {
    LDA_CanLoadValue(I8080_OpCodes::LDA, 0xFF, 0x0123);
}

TEST_F(I8080_LDAFixture, LDA_CanLoadValue_3) {
    LDA_CanLoadValue(I8080_OpCodes::LDA, 0xAE, 0x4444);
}

TEST_F(I8080_LDAFixture, LDA_CanLoadValue_4) {
    LDA_CanLoadValue(I8080_OpCodes::LDA, 0xDA, 0x0003);
}

TEST_F(I8080_LDAFixture, LDAX_B_CanLoadValue_1) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_B, 0x25, cpu.B, 0x1234);
}

TEST_F(I8080_LDAFixture, LDAX_B_CanLoadValue_2) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_B, 0xFF, cpu.B, 0x0123);
}

TEST_F(I8080_LDAFixture, LDAX_B_CanLoadValue_3) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_B, 0xAE, cpu.B, 0x4444);
}

TEST_F(I8080_LDAFixture, LDAX_B_CanLoadValue_4) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_B, 0xDA, cpu.B, 0x0001);
}

TEST_F(I8080_LDAFixture, LDAX_D_CanLoadValue_1) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_D, 0x25, cpu.D, 0x1234);
}

TEST_F(I8080_LDAFixture, LDAX_D_CanLoadValue_2) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_D, 0xFF, cpu.D, 0x0123);
}

TEST_F(I8080_LDAFixture, LDAX_D_CanLoadValue_3) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_D, 0xAE, cpu.D, 0x4444);
}

TEST_F(I8080_LDAFixture, LDAX_D_CanLoadValue_4) {
    LDAX_CanLoadValue(I8080_OpCodes::LDAX_D, 0xDA, cpu.D, 0x0001);
}
