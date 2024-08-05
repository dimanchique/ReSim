#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_AA) {
    MOV_CanDoNopLikeMove(MOV_A_A);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AB) {
    MOV_CanMoveRegToReg(MOV_A_B, cpu.A, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AC) {
    MOV_CanMoveRegToReg(MOV_A_C, cpu.A, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AD) {
    MOV_CanMoveRegToReg(MOV_A_D, cpu.A, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AE) {
    MOV_CanMoveRegToReg(MOV_A_E, cpu.A, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AH) {
    MOV_CanMoveRegToReg(MOV_A_H, cpu.A, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AL) {
    MOV_CanMoveRegToReg(MOV_A_L, cpu.A, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AM) {
    MOV_CanMoveMemToReg(MOV_A_M, cpu.A, 0x1234, 0x23);
}
