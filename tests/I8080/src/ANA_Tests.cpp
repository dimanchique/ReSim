#include "I8080_TestingSuite.h"

class I8080_ANAFixture : public I8080_TestFixture {
public:
    void ANA_CanDoAndWithRegister(const I8080_OpCodes opcode, const BYTE accValue, BYTE &targetRegister, const BYTE value) {
        // given:
        cpu.A = accValue;
        targetRegister = value;
        mem[0x0000] = opcode;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue & value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }

    void ANA_CanDoAndWithMemory(const BYTE accValue, const WORD destMemoryAddress, const BYTE value){
        // given:
        cpu.A = accValue;
        mem[destMemoryAddress] = value;
        mem[0x0000] = I8080_OpCodes::ANA_M;
        I8080::wordToRegisterSwapped(destMemoryAddress, cpu.H, cpu.L);

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue & value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

// or accumulator with itself is kinda strange but ok
TEST_F(I8080_ANAFixture, ANA_A) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_A, 0b00100101, cpu.A, 0b00100101); // -> 0b00100101
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_B) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_B, 0b01111111, cpu.B, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_B_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_B, 0b00000000, cpu.B, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_B_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_B, 0b10000011, cpu.B, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_B_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_B, 0b10000001, cpu.B, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_C) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_C, 0b01111111, cpu.C, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_C_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_C, 0b00000000, cpu.C, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_C_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_C, 0b10000011, cpu.C, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_C_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_C, 0b10000001, cpu.C, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_D) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_D, 0b01111111, cpu.D, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_D_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_D, 0b00000000, cpu.D, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_D_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_D, 0b10000011, cpu.D, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_D_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_D, 0b10000001, cpu.D, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_E) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_E, 0b01111111, cpu.E, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_E_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_E, 0b00000000, cpu.E, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_E_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_E, 0b10000011, cpu.E, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_E_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_E, 0b10000001, cpu.E, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_H) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_H, 0b01111111, cpu.H, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_H_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_H, 0b00000000, cpu.H, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_H_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_H, 0b10000011, cpu.H, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_H_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_H, 0b10000001, cpu.H, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_L) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_L, 0b01111111, cpu.L, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_L_Zero) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_L, 0b00000000, cpu.L, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_L_Signed_NoParity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_L, 0b10000011, cpu.L, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_L_Signed_Parity) {
    ANA_CanDoAndWithRegister(I8080_OpCodes::ANA_L, 0b10000001, cpu.L, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_M) {
    ANA_CanDoAndWithMemory(0b01111111, 0x1234, 0b00111111); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_M_Zero) {
    ANA_CanDoAndWithMemory(0b00000000, 0x1234, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_M_Signed_NoParity) {
    ANA_CanDoAndWithMemory(0b10000011, 0x1234, 0b11111111); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ANAFixture, ANA_M_Signed_Parity) {
    ANA_CanDoAndWithMemory(0b10000001, 0x1234, 0b11000011); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
