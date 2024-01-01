#pragma once
#include "I8080_TestingSuite.h"

class I8080_MOVFixture : public I8080_TestFixture {
public:
    void RegToRegMov(I8080_OpCodes opcode, BYTE& destRegister, BYTE& srcRegister, BYTE value);
    void MemToRegMov(I8080_OpCodes opcode, BYTE& destRegister, WORD srcMemoryAddress, BYTE value);
    void RegToMemMov(I8080_OpCodes opcode, WORD destMemoryAddress, BYTE value);
    void NopLikeMov(I8080_OpCodes opcode);
};
