#pragma once
#include "I8080_TestingSuite.h"

class I8080_MOVFixture : public I8080_TestFixture {
public:
    void MOV_CanMoveRegToReg(I8080_OpCodes opcode, BYTE& destRegister, BYTE& srcRegister, BYTE value);
    void MOV_CanMoveMemToReg(I8080_OpCodes opcode, BYTE& destRegister, WORD srcMemoryAddress, BYTE value);
    void MOV_CanMoveRegToMem(I8080_OpCodes opcode, WORD destMemoryAddress, BYTE value);
    void MOV_CanDoNopLikeMove(I8080_OpCodes opcode);
};
