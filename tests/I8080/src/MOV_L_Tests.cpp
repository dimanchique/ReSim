#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_LA) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_A, cpu.L, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LB) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_B, cpu.L, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LC) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_C, cpu.L, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LD) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_D, cpu.L, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LE) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_E, cpu.L, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LH) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_L_H, cpu.L, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LL) {
    MOV_CanDoNopLikeMove(I8080_OpCodes::MOV_L_L);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LM) {
    MOV_CanMoveMemToReg(I8080_OpCodes::MOV_L_M, cpu.L, 0x1234, 0x23);
}
