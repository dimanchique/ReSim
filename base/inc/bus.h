#pragma once

#include <functional>
#include "core/types.h"
#include "map"
#include "exception"

template<typename BusWidth>
class Bus {
public:
    void Attach(IO_Device<BusWidth>* io_device, BusWidth startAddr, BusWidth endAddr) {
        if (auto it = regions.lower_bound(startAddr); it != regions.end()) {
            if (regions.find(startAddr - 1) == regions.end())
                regions[startAddr - 1] = it->second;
        }

        regions[startAddr] = io_device;
        regions[endAddr] = io_device;
        if (auto it = regions.upper_bound(startAddr); it != regions.end()) {
            regions[endAddr + 1] = it->second;
        }
    }

    void Write(BusWidth address, BYTE value) {
        FindDevice(address)->Write(address, value);
    }

    BYTE Read(BusWidth address) {
        return FindDevice(address)->Read(address);
    }

private:

    IO_Device<BusWidth>* FindDevice(BusWidth address) {
        if (auto it = regions.find(address); it != regions.end()) {
            return it->second;
        }

        if (auto it = regions.upper_bound(address); it != regions.end()) {
            return it->second;
        }

        throw std::out_of_range("No device mapped to address " + std::to_string(address));
    }

    std::map<BusWidth, IO_Device<BusWidth>*> regions;
};
