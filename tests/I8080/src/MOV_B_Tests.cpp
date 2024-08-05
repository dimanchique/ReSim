#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_BA) {
    MOV_CanMoveRegToReg(MOV_B_A, cpu.B, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BB) {
    MOV_CanDoNopLikeMove(MOV_B_B);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BC) {
    MOV_CanMoveRegToReg(MOV_B_C, cpu.B, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BD) {
    MOV_CanMoveRegToReg(MOV_B_D, cpu.B, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BE) {
    MOV_CanMoveRegToReg(MOV_B_E, cpu.B, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BH) {
    MOV_CanMoveRegToReg(MOV_B_H, cpu.B, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BL) {
    MOV_CanMoveRegToReg(MOV_B_L, cpu.B, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BM) {
    MOV_CanMoveMemToReg(MOV_B_M, cpu.B, 0x1234, 0x23);
}
