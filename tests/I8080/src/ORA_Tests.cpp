#include "I8080_TestingSuite.h"

class I8080_ORAFixture : public I8080_TestFixture {
public:
    void ORA_CanDoOrWithRegister(I8080_OpCodes opcode, BYTE accValue, BYTE& targetRegister, BYTE value) {
        // given:
        cpu.A = accValue;
        targetRegister = value;
        mem[0x0000] = opcode;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue | value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }

    void ORA_CanDoOrWithMemory(BYTE accValue, WORD destMemoryAddress, BYTE value){
        // given:
        cpu.A = accValue;
        mem[destMemoryAddress] = value;
        mem[0x0000] = I8080_OpCodes::ORA_M;
        I8080::SwapWordToRegisters(destMemoryAddress, cpu.H, cpu.L);

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue | value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

// or accumulator with itself is kinda strange but ok
TEST_F(I8080_ORAFixture, ORA_A) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_A, 0x25, cpu.A, 0x25); // -> 0x25 (0b00100101)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_B, 0x1F, cpu.B, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_B, 0x0, cpu.B, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_B, 0x80, cpu.B, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_B, 0x80, cpu.B, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_C, 0x1F, cpu.C, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_C, 0x0, cpu.C, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_C, 0x80, cpu.C, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_C, 0x80, cpu.C, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_D, 0x1F, cpu.D, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_D, 0x0, cpu.D, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_D, 0x80, cpu.D, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_D, 0x80, cpu.D, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_E, 0x1F, cpu.E, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_E, 0x0, cpu.E, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_E, 0x80, cpu.E, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_E, 0x80, cpu.E, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_H, 0x1F, cpu.H, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_H, 0x0, cpu.H, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_H, 0x80, cpu.H, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_H, 0x80, cpu.H, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_L, 0x1F, cpu.L, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Zero) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_L, 0x0, cpu.L, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Signed_NoParity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_L, 0x80, cpu.L, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Signed_Parity) {
    ORA_CanDoOrWithRegister(I8080_OpCodes::ORA_L, 0x80, cpu.L, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M) {
    ORA_CanDoOrWithMemory(0x1F, 0x1234, 0x25); // -> 0x3f (0b00111111)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Zero) {
    ORA_CanDoOrWithMemory(0x0, 0x1234, 0x0); // -> 0x0 (0b00000000)
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Signed_NoParity) {
    ORA_CanDoOrWithMemory(0x80, 0x1234, 0x03); // -> 0xFF (0b10000011)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Signed_Parity) {
    ORA_CanDoOrWithMemory(0x80, 0x1234, 0x01); // -> 0x81 (0b10000001)
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
