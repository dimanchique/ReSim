#include "I8086_ImpliedOpTests.h"

class I8086_LAHF_SAHF_Fixture : public I8086_ImpliedOpFixture {};

TEST_F(I8086_LAHF_SAHF_Fixture, SAHF_CanStoreAH_1) {
    cpu.Status.Value = 0x0000;
    cpu.AH = 0xFF;
    TestImpliedInstruction(SAHF);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.S);
}

TEST_F(I8086_LAHF_SAHF_Fixture, SAHF_CanStoreAH_2) {
    cpu.Status.Value = 0x0000;
    cpu.AH = 0x0F;
    TestImpliedInstruction(SAHF);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_LAHF_SAHF_Fixture, SAHF_CanStoreAH_3) {
    cpu.Status.Value = 0x0000;
    cpu.AH = 0xF0;
    TestImpliedInstruction(SAHF);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.S);
}

TEST_F(I8086_LAHF_SAHF_Fixture, LAHF_CanLoadAH_1) {
    cpu.Status.Value = 0x0000;
    cpu.AH = 0xFF;
    TestImpliedInstruction(LAHF);
    EXPECT_EQ(cpu.AH, 0x00);
}

TEST_F(I8086_LAHF_SAHF_Fixture, LAHF_CanLoadAH_2) {
    cpu.Status.Value = 0x00FF;
    cpu.AH = 0x00;
    TestImpliedInstruction(LAHF);
    EXPECT_EQ(cpu.AH, 0xFF);
}

TEST_F(I8086_LAHF_SAHF_Fixture, LAHF_CanLoadAH_3) {
    cpu.Status.Value = 0x00F0;
    cpu.AH = 0x0F;
    TestImpliedInstruction(LAHF);
    EXPECT_EQ(cpu.AH, 0xF0);
}
