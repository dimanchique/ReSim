#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_EA) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_A, cpu.E, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EB) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_B, cpu.E, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EC) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_C, cpu.E, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_ED) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_D, cpu.E, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EE) {
    MOV_CanDoNopLikeMove(I8080_OpCodes::MOV_E_E);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EH) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_H, cpu.E, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EL) {
    MOV_CanMoveRegToReg(I8080_OpCodes::MOV_E_L, cpu.E, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_EM) {
    MOV_CanMoveMemToReg(I8080_OpCodes::MOV_E_M, cpu.E, 0x1234, 0x23);
}
