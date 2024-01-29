#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_MA) {
    cpu.A = 0x23;
    MOV_CanMoveRegToMem(I8080_OpCodes::MOV_M_A, 0x1234, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_MB) {
    cpu.B = 0x23;
    MOV_CanMoveRegToMem(I8080_OpCodes::MOV_M_B, 0x1234, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_MC) {
    cpu.C = 0x23;
    MOV_CanMoveRegToMem(I8080_OpCodes::MOV_M_C, 0x1234, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_MD) {
    cpu.D = 0x23;
    MOV_CanMoveRegToMem(I8080_OpCodes::MOV_M_D, 0x1234, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_ME) {
    cpu.E = 0x23;
    MOV_CanMoveRegToMem(I8080_OpCodes::MOV_M_E, 0x1234, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_MH) {
    // given:
    mem[0x1234] = 0;
    mem[0x0000] = I8080_OpCodes::MOV_M_H;
    I8080::wordToRegisterSwapped(0x1234, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x1234], 0x12);
    CheckCyclesCount();
}

TEST_F(I8080_MOVFixture, ExecuteMOV_ML) {
    // given:
    mem[0x1234] = 0;
    mem[0x0000] = I8080_OpCodes::MOV_M_L;
    I8080::wordToRegisterSwapped(0x1234, cpu.H, cpu.L);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x1234], 0x34);
    CheckCyclesCount();
}
