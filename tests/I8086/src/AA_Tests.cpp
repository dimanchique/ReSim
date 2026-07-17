#include "I8086_ImpliedOpTests.h"

class I8086_AA_Fixture : public I8086_ImpliedOpFixture {};

TEST_F(I8086_AA_Fixture, AAA_NoAdjust) {
    cpu.AL = 0x03;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAA);

    EXPECT_EQ(cpu.AL, 0x03);
    EXPECT_EQ(cpu.AH, 0x42);
    EXPECT_EQ(cpu.Status.A, 0);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_AA_Fixture, AAA_AdjustLowNibble) {
    cpu.AL = 0x0D;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAA);

    EXPECT_EQ(cpu.AL, 0x03);
    EXPECT_EQ(cpu.AH, 0x43);
    EXPECT_EQ(cpu.Status.A, 1);
    EXPECT_EQ(cpu.Status.C, 1);
}

TEST_F(I8086_AA_Fixture, AAA_AdjustAF) {
    cpu.AL = 0x05;
    cpu.AH = 0x42;
    cpu.Status.A = 1;

    TestImpliedInstruction(AAA);

    EXPECT_EQ(cpu.AL, 0x0B);
    EXPECT_EQ(cpu.AH, 0x43);
    EXPECT_EQ(cpu.Status.A, 1);
    EXPECT_EQ(cpu.Status.C, 1);
}

TEST_F(I8086_AA_Fixture, AAA_ZeroNoAdjust) {
    cpu.AL = 0x00;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAA);

    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_EQ(cpu.AH, 0x42);
    EXPECT_EQ(cpu.Status.A, 0);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_AA_Fixture, AAS_NoAdjust) {
    cpu.AL = 0x05;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAS);

    EXPECT_EQ(cpu.AL, 0x05);
    EXPECT_EQ(cpu.AH, 0x42);
    EXPECT_EQ(cpu.Status.A, 0);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_AA_Fixture, AAS_AdjustLowNibble) {
    cpu.AL = 0x0D;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAS);

    EXPECT_EQ(cpu.AL, 0x07);
    EXPECT_EQ(cpu.AH, 0x41);
    EXPECT_EQ(cpu.Status.A, 1);
    EXPECT_EQ(cpu.Status.C, 1);
}

TEST_F(I8086_AA_Fixture, AAS_AdjustAF) {
    cpu.AL = 0x05;
    cpu.AH = 0x42;
    cpu.Status.A = 1;

    TestImpliedInstruction(AAS);

    EXPECT_EQ(cpu.AL, 0x0F);
    EXPECT_EQ(cpu.AH, 0x41);
    EXPECT_EQ(cpu.Status.A, 1);
    EXPECT_EQ(cpu.Status.C, 1);
}

TEST_F(I8086_AA_Fixture, AAS_ZeroNoAdjust) {
    cpu.AL = 0x00;
    cpu.AH = 0x42;

    TestImpliedInstruction(AAS);

    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_EQ(cpu.AH, 0x42);
    EXPECT_EQ(cpu.Status.A, 0);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_AA_Fixture, AAM_Simple) {
    cpu.AL = 0x3A;

    TestImpliedInstruction(AAM);

    EXPECT_EQ(cpu.AH, 0x05);
    EXPECT_EQ(cpu.AL, 0x08);
    EXPECT_EQ(cpu.Status.S, 0);
    EXPECT_EQ(cpu.Status.Z, 0);
    EXPECT_EQ(cpu.Status.P, 0);
}

TEST_F(I8086_AA_Fixture, AAM_Zero) {
    cpu.AL = 0x00;

    TestImpliedInstruction(AAM);

    EXPECT_EQ(cpu.AH, 0x00);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_EQ(cpu.Status.S, 0);
    EXPECT_EQ(cpu.Status.Z, 1);
    EXPECT_EQ(cpu.Status.P, 1);
}

TEST_F(I8086_AA_Fixture, AAM_SmallValue) {
    cpu.AL = 0x05;

    TestImpliedInstruction(AAM);

    EXPECT_EQ(cpu.AH, 0x00);
    EXPECT_EQ(cpu.AL, 0x05);
    EXPECT_EQ(cpu.Status.S, 0);
    EXPECT_EQ(cpu.Status.Z, 0);
    EXPECT_EQ(cpu.Status.P, 1);
}

TEST_F(I8086_AA_Fixture, AAD_Simple) {
    cpu.AH = 0x03;
    cpu.AL = 0x05;

    TestImpliedInstruction(AAD);

    EXPECT_EQ(cpu.AL, 0x23);
    EXPECT_EQ(cpu.AH, 0x00);
    EXPECT_EQ(cpu.Status.S, 0);
    EXPECT_EQ(cpu.Status.Z, 0);
    EXPECT_EQ(cpu.Status.P, 0);
}

TEST_F(I8086_AA_Fixture, AAD_Zero) {
    cpu.AH = 0x00;
    cpu.AL = 0x00;

    TestImpliedInstruction(AAD);

    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_EQ(cpu.AH, 0x00);
    EXPECT_EQ(cpu.Status.S, 0);
    EXPECT_EQ(cpu.Status.Z, 1);
    EXPECT_EQ(cpu.Status.P, 1);
}

TEST_F(I8086_AA_Fixture, AAD_NegativeResult) {
    cpu.AH = 0x10;
    cpu.AL = 0x09;

    TestImpliedInstruction(AAD);

    EXPECT_EQ(cpu.AL, 0xA9);
    EXPECT_EQ(cpu.AH, 0x00);
    EXPECT_EQ(cpu.Status.S, 1);
    EXPECT_EQ(cpu.Status.Z, 0);
    EXPECT_EQ(cpu.Status.P, 1);
}
