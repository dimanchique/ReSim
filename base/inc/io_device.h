#pragma once

class IO_Device {
public:
    virtual BYTE Read(U32 address) = 0;
    virtual void Write(U32 address, BYTE value) = 0;

    virtual BYTE &operator[](U32 address) = 0;
};
