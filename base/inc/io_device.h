#pragma once

template<typename BusWidth>
class IO_Device {
public:
    virtual BYTE Read(BusWidth address) = 0;
    virtual void Write(BusWidth address, BYTE value) = 0;

    virtual BYTE &operator[](BusWidth address) = 0;
};
