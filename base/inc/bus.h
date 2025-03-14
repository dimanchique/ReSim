#pragma once

#include <functional>
#include "core/types.h"
#include "map"
#include "exception"

class Bus {
public:
    void SetBusRegion(QWORD startAddr, QWORD endAddr, IO_Device* io_device) {
        if (auto it = regions.lower_bound(startAddr); it != regions.end()) {
            regions[startAddr - 1] = it->second;
        }

        regions[startAddr] = io_device;
        regions[endAddr] = io_device;
    }

    void Write(QWORD address, BYTE value) {
        ExecuteOnDevice(address, [value](IO_Device* device, QWORD addr) {
            device->Write(addr, value);
        });
    }

    BYTE Read(QWORD address) {
        BYTE result = 0;
        ExecuteOnDevice(address, [&result](IO_Device* device, QWORD addr) {
            result = device->Read(addr);
        });
        return result;
    }

private:

    void ExecuteOnDevice(QWORD address, const std::function<void(IO_Device*, QWORD)>& callback) {
        if (auto it = regions.find(address); it != regions.end()) {
            callback(it->second, address);
            return;
        }

        if (auto it = regions.upper_bound(address); it != regions.end()) {
            callback(it->second, address);
            return;
        }

        // if device is not present then do nothing, no need to throw exception
        throw std::out_of_range("No device mapped to address " + std::to_string(address));
    }

    std::map<QWORD, IO_Device*> regions;
};
