#include "I8080_TestingSuite.h"

class I8080_ORAFixture : public I8080_TestFixture {
public:
    void ORA_CanDoOrWithRegister(const I8080_OpCodes opcode, const BYTE accValue, BYTE &targetRegister, const BYTE value) {
        // given:
        cpu.A = accValue;
        targetRegister = value;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue | value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }

    void ORA_CanDoOrWithMemory(const BYTE accValue, const WORD destMemoryAddress, const BYTE value){
        // given:
        cpu.A = accValue;
        mem[destMemoryAddress] = value;
        mem[0x0000] = ORA_M;
        mem[0x0001] = STOP_OPCODE;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(destMemoryAddress, cpu.H, cpu.L);

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
    ORA_CanDoOrWithRegister(ORA_A, 0b00100101, cpu.A, 0b00100101); // -> 0b00100101
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B) {
    ORA_CanDoOrWithRegister(ORA_B, 0b00011111, cpu.B, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Zero) {
    ORA_CanDoOrWithRegister(ORA_B, 0b00000000, cpu.B, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_B, 0b10000000, cpu.B, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_B_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_B, 0b10000000, cpu.B, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C) {
    ORA_CanDoOrWithRegister(ORA_C, 0b00011111, cpu.C, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Zero) {
    ORA_CanDoOrWithRegister(ORA_C, 0b00000000, cpu.C, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_C, 0b10000000, cpu.C, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_C_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_C, 0b10000000, cpu.C, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D) {
    ORA_CanDoOrWithRegister(ORA_D, 0b00011111, cpu.D, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Zero) {
    ORA_CanDoOrWithRegister(ORA_D, 0b00000000, cpu.D, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_D, 0b10000000, cpu.D, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_D_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_D, 0b10000000, cpu.D, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E) {
    ORA_CanDoOrWithRegister(ORA_E, 0b00011111, cpu.E, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Zero) {
    ORA_CanDoOrWithRegister(ORA_E, 0b00000000, cpu.E, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_E, 0b10000000, cpu.E, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_E_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_E, 0b10000000, cpu.E, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H) {
    ORA_CanDoOrWithRegister(ORA_H, 0b00011111, cpu.H, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Zero) {
    ORA_CanDoOrWithRegister(ORA_H, 0b00000000, cpu.H, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_H, 0b10000000, cpu.H, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_H_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_H, 0b10000000, cpu.H, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L) {
    ORA_CanDoOrWithRegister(ORA_L, 0b00011111, cpu.L, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Zero) {
    ORA_CanDoOrWithRegister(ORA_L, 0b00000000, cpu.L, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Signed_NoParity) {
    ORA_CanDoOrWithRegister(ORA_L, 0b10000000, cpu.L, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_L_Signed_Parity) {
    ORA_CanDoOrWithRegister(ORA_L, 0b10000000, cpu.L, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M) {
    ORA_CanDoOrWithMemory(0b00011111, 0x1234, 0b00100101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Zero) {
    ORA_CanDoOrWithMemory(0b00000000, 0x1234, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Signed_NoParity) {
    ORA_CanDoOrWithMemory(0b10000000, 0x1234, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_ORAFixture, ORA_M_Signed_Parity) {
    ORA_CanDoOrWithMemory(0b10000000, 0x1234, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
