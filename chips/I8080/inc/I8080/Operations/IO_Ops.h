#pragma once
#include "I8080/I8080.h"

/**
 * @brief Read byte of data from external device and store it in Accumulator
 * @short A = DataBus[Device_ID]
 * @param cpu I8080 struct instance.
 */
void I8080_IN(I8080 &cpu) {
    const BYTE deviceAddress = cpu.FetchByte();
    cpu.A = cpu.GetDataBus()->Read(deviceAddress);
}

/**
 * @brief Send Accumulator data to external device
 * @short DataBus[Device_ID] = A
 * @param cpu I8080 struct instance.
 */
void I8080_OUT(I8080 &cpu) {
    const BYTE deviceAddress = cpu.FetchByte();
    cpu.GetDataBus()->Write(deviceAddress, cpu.A);
}
