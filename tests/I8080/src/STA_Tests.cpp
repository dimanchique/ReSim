#include "I8080_TestingSuite.h"

class I8080_STAFixture : public I8080_TestFixture {
public:
    void STA_CanStoreValue(I8080_OpCodes opcode, BYTE initialValue, WORD memoryAddress) {
        // given:
        cpu.A = initialValue;
        mem[0x0000] = opcode;
        mem[0x0001] = (memoryAddress >> 8) & 0xFF;
        mem[0x0002] = memoryAddress & 0xFF;

        cyclesExpected = 13;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], cpu.A);
        CheckCyclesCount();
    }

    void STAX_CanStoreValue(I8080_OpCodes opcode, BYTE initialValue, WORD memoryAddress) {
        // given:
        cpu.A = initialValue;
        mem[0x0000] = opcode;

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(mem[memoryAddress], cpu.A);
        CheckCyclesCount();
    }
};

TEST_F(I8080_STAFixture, STA_CanStoreValue_1) {
    STA_CanStoreValue(I8080_OpCodes::STA, 0x25, 0x1234);
}

TEST_F(I8080_STAFixture, STA_CanStoreValue_2) {
    STA_CanStoreValue(I8080_OpCodes::STA, 0xFF, 0x0123);
}

TEST_F(I8080_STAFixture, STA_CanStoreValue_3) {
    STA_CanStoreValue(I8080_OpCodes::STA, 0xAE, 0x4444);
}

TEST_F(I8080_STAFixture, STA_CanStoreValue_4) {
    STA_CanStoreValue(I8080_OpCodes::STA, 0xDA, 0x0003);
}

TEST_F(I8080_STAFixture, STAX_B_CanStoreValue_1) {
    I8080::SwapWordToRegisters(0x1234, cpu.B, cpu.C);
    STAX_CanStoreValue(I8080_OpCodes::STAX_B, 0x25, 0x1234);
}

TEST_F(I8080_STAFixture, STAX_B_CanStoreValue_2) {
    I8080::SwapWordToRegisters(0x0123, cpu.B, cpu.C);
    STAX_CanStoreValue(I8080_OpCodes::STAX_B, 0xFF, 0x0123);
}

TEST_F(I8080_STAFixture, STAX_B_CanStoreValue_3) {
    I8080::SwapWordToRegisters(0x4444, cpu.B, cpu.C);
    STAX_CanStoreValue(I8080_OpCodes::STAX_B, 0xAE, 0x4444);
}

TEST_F(I8080_STAFixture, STAX_B_CanStoreValue_4) {
    I8080::SwapWordToRegisters(0x0001, cpu.B, cpu.C);
    STAX_CanStoreValue(I8080_OpCodes::STAX_B, 0xDA, 0x0001);
}

TEST_F(I8080_STAFixture, STAX_D_CanStoreValue_1) {
    I8080::SwapWordToRegisters(0x1234, cpu.D, cpu.E);
    STAX_CanStoreValue(I8080_OpCodes::STAX_D, 0x25, 0x1234);
}

TEST_F(I8080_STAFixture, STAX_D_CanStoreValue_2) {
    I8080::SwapWordToRegisters(0x0123, cpu.D, cpu.E);
    STAX_CanStoreValue(I8080_OpCodes::STAX_D, 0xFF, 0x0123);
}

TEST_F(I8080_STAFixture, STAX_D_CanStoreValue_3) {
    I8080::SwapWordToRegisters(0x4444, cpu.D, cpu.E);
    STAX_CanStoreValue(I8080_OpCodes::STAX_D, 0xAE, 0x4444);
}

TEST_F(I8080_STAFixture, STAX_D_CanStoreValue_4) {
    I8080::SwapWordToRegisters(0x0001, cpu.D, cpu.E);
    STAX_CanStoreValue(I8080_OpCodes::STAX_D, 0xDA, 0x0001);
}
