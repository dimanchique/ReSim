#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_HA) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_A, cpu.H, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HB) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_B, cpu.H, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HC) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_C, cpu.H, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HD) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_D, cpu.H, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HE) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_E, cpu.H, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HH) {
    MOV_CanDoNopLikeMove(I8080_OpCodes::MOV_H_H);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HL) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_H_L, cpu.H, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_HM) {
    MOV_CanMoveMemToReg(I8080_OpCodes::MOV_H_M, cpu.H, 0x1234, 0x23);
}
