#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_DA) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_A, cpu.D, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DB) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_B, cpu.D, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DC) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_C, cpu.D, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DD) {
    MOV_CanDoNopLikeMove(I8080_OpCodes::MOV_D_D);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DE) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_E, cpu.D, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DH) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_H, cpu.D, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DL) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_D_L, cpu.D, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_DM) {
    MOV_CanMoveMemToReg(I8080_OpCodes::MOV_D_M, cpu.D, 0x1234, 0x23);
}
