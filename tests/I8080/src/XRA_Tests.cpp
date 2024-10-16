#include "I8080_TestingSuite.h"

class I8080_XRAFixture : public I8080_TestFixture {
public:
    void XRA_CanDoXorWithRegister(const I8080_OpCodes opcode, const BYTE accValue, BYTE &targetRegister, const BYTE value) {
        // given:
        cpu.A = accValue;
        targetRegister = value;
        mem[0x0000] = opcode;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue ^ value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }

    void XRA_CanDoXorWithMemory(const BYTE accValue, const WORD destMemoryAddress, const BYTE value){
        // given:
        cpu.A = accValue;
        mem[destMemoryAddress] = value;
        mem[0x0000] = XRA_M;
        mem[0x0001] = STOP_OPCODE;
        ReSimFunctionLibrary::ContentManipulation::putWordToBytesSwapped_Ref(destMemoryAddress, cpu.H, cpu.L);

        cyclesExpected = 7;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, accValue ^ value);
        EXPECT_FALSE(cpu.Status.C); // always reset
        CheckCyclesCount();
    }
};

// xor accumulator with itself is kinda strange but ok
TEST_F(I8080_XRAFixture, XRA_A) {
    XRA_CanDoXorWithRegister(XRA_A, 0b00010101, cpu.A, 0b00010101); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_B) {
    XRA_CanDoXorWithRegister(XRA_B, 0b00101010, cpu.B, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_B_Zero) {
    XRA_CanDoXorWithRegister(XRA_B, 0b00000000, cpu.B, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_B_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_B, 0b10000000, cpu.B, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_B_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_B, 0b10000000, cpu.B, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_C) {
    XRA_CanDoXorWithRegister(XRA_C, 0b00101010, cpu.C, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_C_Zero) {
    XRA_CanDoXorWithRegister(XRA_C, 0b00000000, cpu.C, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_C_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_C, 0b10000000, cpu.C, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_C_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_C, 0b10000000, cpu.C, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_D) {
    XRA_CanDoXorWithRegister(XRA_D, 0b00101010, cpu.D, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_D_Zero) {
    XRA_CanDoXorWithRegister(XRA_D, 0b00000000, cpu.D, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_D_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_D, 0b10000000, cpu.D, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_D_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_D, 0b10000000, cpu.D, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_E) {
    XRA_CanDoXorWithRegister(XRA_E, 0b00101010, cpu.E, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_E_Zero) {
    XRA_CanDoXorWithRegister(XRA_E, 0b00000000, cpu.E, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_E_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_E, 0b10000000, cpu.E, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_E_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_E, 0b10000000, cpu.E, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_H) {
    XRA_CanDoXorWithRegister(XRA_H, 0b00101010, cpu.H, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_H_Zero) {
    XRA_CanDoXorWithRegister(XRA_H, 0b00000000, cpu.H, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_H_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_H, 0b10000000, cpu.H, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_H_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_H, 0b10000000, cpu.H, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_L) {
    XRA_CanDoXorWithRegister(XRA_L, 0b00101010, cpu.L, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_L_Zero) {
    XRA_CanDoXorWithRegister(XRA_L, 0b00000000, cpu.L, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_L_Signed_NoParity) {
    XRA_CanDoXorWithRegister(XRA_L, 0b10000000, cpu.L, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_L_Signed_Parity) {
    XRA_CanDoXorWithRegister(XRA_L, 0b10000000, cpu.L, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_M) {
    XRA_CanDoXorWithMemory(0b00101010, 0x1234, 0b00010101); // -> 0b00111111
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_M_Zero) {
    XRA_CanDoXorWithMemory(0b00000000, 0x1234, 0b00000000); // -> 0b00000000
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_M_Signed_NoParity) {
    XRA_CanDoXorWithMemory(0b10000000, 0x1234, 0b00000011); // -> 0b10000011
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8080_XRAFixture, XRA_M_Signed_Parity) {
    XRA_CanDoXorWithMemory(0b10000000, 0x1234, 0b00000001); // -> 0b10000001
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}
