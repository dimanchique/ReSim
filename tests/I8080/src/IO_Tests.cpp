#include "I8080_TestingSuite.h"

class I8080_IOFixture : public I8080_TestFixture {};

class TestInputDevice : public IO_Device<WORD> {
public:
    void Write(WORD address, BYTE value) override {
        device_value = value;
    }

    BYTE Read(WORD address) override {
        return device_value;
    }

    BYTE &operator[](WORD address) override {
        return device_value;
    }

    BYTE device_value = 0;
};

TEST_F(I8080_IOFixture, IN_CanReadValue) {
    cpu.A = 0;
    BYTE device_value = 0xDA;
    BYTE device_address = 0xAE;

    mem[0x0000] = IN;
    mem[0x0001] = device_address;
    mem[0x0002] = RET;

    TestInputDevice io_device;
    io_device.device_value = device_value;

    Bus<WORD> data_bus;
    cpu.SetDataBusInstance(&data_bus);
    data_bus.Attach(&io_device, device_address, device_address);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, device_value);
    CheckCyclesCount();
}

TEST_F(I8080_IOFixture, OUT_CanWriteValue) {
    cpu.A = 0xDA;
    BYTE device_value = 0x00;
    BYTE device_address = 0xAE;

    mem[0x0000] = OUT;
    mem[0x0001] = device_address;
    mem[0x0002] = RET;

    TestInputDevice io_device;
    io_device.device_value = device_value;

    Bus<WORD> data_bus;
    cpu.SetDataBusInstance(&data_bus);
    data_bus.Attach(&io_device, device_address, device_address);

    cyclesExpected = 7;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(io_device.device_value, cpu.A);
    CheckCyclesCount();
}
